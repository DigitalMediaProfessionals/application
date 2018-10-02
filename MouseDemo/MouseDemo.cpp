#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <signal.h>
#include <sys/wait.h>

#include "util_draw.h"
#include "util_input.h"
#include "usb-mouse.h"

#include <errno.h>
#include <paths.h>
#include <grp.h>
#include <sys/stat.h>

using namespace std;
using namespace dmp;
using namespace util;

#define SCREEN_W 1280
#define SCREEN_H 720

#define MAX_APPS 20
#define MAX_APP_TYPES 5
#define MAX_BOXES 13
#define SEGMENT_MODE 0
#define DETECT_MODE 1
#define OTHER_MODE 2
#define DMP_COLOR 0xFF0D97D2

#ifndef OPEN_MAX
#define OPEN_MAX 256
#endif

enum flip_y_e { flip_y = true };

volatile bool flag = false;
volatile bool exit_code = false;
int box_area[MAX_BOXES][4];
int screen_mode;
int next_page = 0;
int l_next_page = 0;
int more_types = 0;
bool st_changed = false;
bool previous_bt_ready = false;
bool next_bt_ready = false;
int rboxes_will_draw = 0;
bool up_bt_ready = false;
bool down_bt_ready = false;
int lboxes_will_draw = 0;

mouse_infor m_cur;
COverlayRGB bg_overlay(SCREEN_W, SCREEN_H);
COverlayRGB boxes_overlay(SCREEN_W, SCREEN_H);

//Set the link for the font file.
string font_file = "font/NotoSerif-Black.ttf";

struct app_infor{
  string name;
  string bin_address;
  string is_cam;
};

struct apps{
  string type_name;
  app_infor app_num[20];
  int amount;
};
apps app_type[ MAX_APP_TYPES];

typedef struct {
  FILE *read_fd;
  FILE *write_fd;
  pid_t child_pid;
} SPC_PIPE;


static int open_devnull(int fd) {
  FILE *f = 0;
  if (!fd) f = freopen(_PATH_DEVNULL, "rb", stdin);
  else if (fd == 1) f = freopen(_PATH_DEVNULL, "wb", stdout);
  else if (fd == 2) f = freopen(_PATH_DEVNULL, "wb", stderr);
  return (f && fileno(f) == fd);
}

static int orig_ngroups = -1;
static gid_t orig_gid = -1;
static uid_t orig_uid = -1;
static gid_t orig_groups[NGROUPS_MAX];

void spc_drop_privileges(int permanent) {
  gid_t newgid = getgid( ), oldgid = getegid( );
  uid_t newuid = getuid( ), olduid = geteuid( );
  if (!permanent) {
    /* Save information about the privileges that are being dropped so that they
    * can be restored later.
    */
    orig_gid = oldgid;
    orig_uid = olduid;
    orig_ngroups = getgroups(NGROUPS_MAX, orig_groups);
  }
  /* If root privileges are to be dropped, be sure to pare down the ancillary
  * groups for the process before doing anything else because the setgroups( )
  * system call requires root privileges. Drop ancillary groups regardless of
  * whether privileges are being dropped temporarily or permanently.
  */
  if ( !olduid) setgroups(1, &newgid);
  if ( newgid != oldgid) {
    #if !defined( linux)
    if( setegid(newgid) == -1){};
    if ( permanent && setgid(newgid) == -1) abort();
    #else
    if ( setregid(( permanent ? newgid : -1), newgid) == -1) abort();
    #endif
  }
  if (newuid != olduid) {
    #if !defined(linux)
    if( seteuid(newuid) == -1){};
    if (permanent && setuid(newuid) == -1) abort( );
    #else
    if (setreuid((permanent ? newuid : -1), newuid) == -1) abort( );
    #endif
  }
  /* verify that the changes were successful */
  if (permanent) {
    if (newgid != oldgid && (setegid(oldgid) != -1 || getegid( ) != newgid))
      abort();
    if (newuid != olduid && (seteuid(olduid) != -1 || geteuid( ) != newuid))
      abort();
  } else {
    if (newgid != oldgid && getegid( ) != newgid) abort( );
    if (newuid != olduid && geteuid( ) != newuid) abort( );
  }
}

void spc_restore_privileges(void) {
  if (geteuid( ) != orig_uid)
  if (seteuid(orig_uid) == -1 || geteuid( ) != orig_uid) abort( );
  if (getegid( ) != orig_gid)
  if (setegid(orig_gid) == -1 || getegid( ) != orig_gid) abort( );
  if (!orig_uid)
  setgroups(orig_ngroups, orig_groups);
}

void spc_sanitize_files(void) {
  int fd, fds;
  struct stat st;
  /* Make sure all open descriptors other than the standard ones are closed */
  if ((fds = getdtablesize( )) == -1) fds = OPEN_MAX;
  for (fd = 3; fd < fds; fd++) close(fd);
  /* Verify that the standard descriptors are open. If they're not, attempt to
  * open them using /dev/null. If any are unsuccessful, abort.
  */
  for (fd = 0; fd < 3; fd++)
    if ( fstat( fd, &st) == -1 && (errno != EBADF || !open_devnull( fd))) abort( ); //fstat( fd, &st) == -1 &&
}

pid_t spc_fork(void) {
  pid_t childpid;
  if ((childpid = fork( )) == -1) return -1;
  /* Reseed PRNGs in both the parent and the child */
  /* See Chapter 11 for examples */
  /* If this is the parent process, there's nothing more to do */
  if (childpid != 0) return childpid;
  /* This is the child process */
  spc_sanitize_files( ); /* Close all open files. See Recipe 1.1 */
  spc_drop_privileges(1); /* Permanently drop privileges. See Recipe 1.3 */
  return 0;
}

SPC_PIPE *spc_popen(const char *path, char *const argv[], char *const envp[]) {
  int stdin_pipe[2], stdout_pipe[2];
  SPC_PIPE *p;
  if (!(p = (SPC_PIPE *)malloc(sizeof(SPC_PIPE)))) return 0;
  p->read_fd = p->write_fd = 0;
  p->child_pid = -1;
  if ( pipe(stdin_pipe) == -1) {
    free(p);
    return 0;
  }
  if (pipe(stdout_pipe) == -1) {
    close(stdin_pipe[1]);
    close(stdin_pipe[0]);
    free(p);
    return 0;
  }
  if (!(p->read_fd = fdopen(stdout_pipe[0], "r"))) {
    close(stdout_pipe[1]);
    close(stdout_pipe[0]);
    close(stdin_pipe[1]);
    close(stdin_pipe[0]);
    free(p);
    return 0;
  }
  if (!(p->write_fd = fdopen(stdin_pipe[1], "w"))) {
    fclose(p->read_fd);
    close(stdout_pipe[1]);
    close(stdin_pipe[1]);
    close(stdin_pipe[0]);
    free(p);
    return 0;
  }
  if ((p->child_pid = spc_fork()) == -1) {
    fclose(p->write_fd);
    fclose(p->read_fd);
    close(stdout_pipe[1]);
    close(stdin_pipe[0]);
    free(p);
    return 0;
  }
  if (!p->child_pid) {
    /* this is the child process */
    close(stdout_pipe[0]);
    close(stdin_pipe[1]);
    if (stdin_pipe[0] != 0) {
    dup2(stdin_pipe[0], 0);
    close(stdin_pipe[0]);
    }
    if (stdout_pipe[1] != 1) {
      dup2(stdout_pipe[1], 1);
      close(stdout_pipe[1]);
    }
    execve(path, argv, envp);
    exit(127);
  }
  close(stdout_pipe[1]);
  close(stdin_pipe[0]);
  return p;
}

int spc_pclose(SPC_PIPE *p) {
  int status;
  pid_t pid = -1;
  if (p->child_pid != -1) {
    do {
      pid = waitpid( p->child_pid, &status, 0);
    } while ( pid == -1 && errno == EINTR);
  }
  if (p->read_fd) fclose(p->read_fd);
  if (p->write_fd) fclose(p->write_fd);
  free(p);
  if ( pid != -1 && WIFEXITED(status)) return WEXITSTATUS(status);
  else return (pid == -1 ? -1 : 0);
}

int rec_area[2][4] = {
    { 100-1, 160-1, 400-1,     720-80-1}, // left area
    { 500-1, 160-1, 1280-100-1, 720-80-1}, // right area
};

void apps_init(){
  for( int i = 0; i < MAX_APP_TYPES; i++){
    app_type[i].type_name = "";
    for( int j = 0; j < MAX_APPS; j++){
      app_type[i].app_num[j].name = "";
      app_type[i].app_num[j].bin_address = "";
      app_type[i].app_num[j].is_cam = "";
    }
    app_type[i].amount = 0;
  }
}

// Reading app information from appList.ini
int get_apps_infor(){ // success -> return True, otherwise return False

  ifstream get_apps( "appList.ini" );
  if ( !get_apps)  return -1;

  apps_init();
  int number_of_apps = 0;

  while( get_apps.good()){
    string app_line;
    getline( get_apps, app_line);

    // Separate app data
    int str_no = 0;
    string str_temp[ 4];
    str_temp[ 0] = "";
    str_temp[ 1] = "";
    str_temp[ 2] = "";
    str_temp[ 3] = "";
    bool stop_fl = false;
    bool cmtLine = false;
    for ( unsigned temp = 0; temp < app_line.size(); temp++){
      string s;
      s = app_line[temp];
      if(( s == "#") && ( cmtLine == false)) {
        cmtLine = true;
        break;
      }
      else{
        if( s == "{") continue;
        else if(( s != "{") && ( s != ",") && (s != "}") && ( stop_fl == false)){
          str_temp[str_no].append( s);
        }
        else if( (s == ",") && ( stop_fl == false))  {
          str_no++;
        }
        else if( s == "}"){
          stop_fl = true;
          continue;
        }
        else{
          // it will never reach here
        }
      }
    }

    // Save app information
    if( cmtLine ==  false){
      for( int ii = 0; ii < MAX_APP_TYPES; ii++){
        if( str_temp[ 0] == app_type[ii].type_name){
          app_type[ii].app_num[ app_type[ii].amount].name = str_temp[ 1];
          app_type[ii].app_num[ app_type[ii].amount].is_cam = str_temp[ 2];
          app_type[ii].app_num[ app_type[ii].amount].bin_address = str_temp[ 3];
          app_type[ii].amount++;
          break;
        }
        else if( app_type[ii].type_name.size() > 0){
          continue;
        }
        else{
          app_type[ii].type_name = str_temp[ 0];
          app_type[ii].app_num[ app_type[ii].amount].name = str_temp[ 1];
          app_type[ii].app_num[ app_type[ii].amount].is_cam = str_temp[ 2];
          app_type[ii].app_num[ app_type[ii].amount].bin_address = str_temp[ 3];
          app_type[ii].amount++;
          break;
        }
      }
      number_of_apps++;
    }
  }

/*    printf( "Number of apps: %d \n", number_of_apps);
    //Display apps information
    for( int ii = 0; ii < MAX_APP_TYPES; ii++){
      printf( "typename: %s \n", app_type[ii].type_name.c_str());
      printf( "app_num.amount: %d \n", app_type[ii].amount);
      for( int jj = 0; jj < app_type[ii].amount; jj++){
      printf( "app_num.name: %s \n", app_type[ii].app_num[jj].name.c_str());
      printf( "app_num.is_cam: %s \n", app_type[ii].app_num[jj].is_cam.c_str());
      printf( "app_num.bin_address: %s \n\n", app_type[ii].app_num[jj].bin_address.c_str());
    }
  }*/

    return number_of_apps;
}

void draw_cursor_to_display( COverlayRGB &ol_screen, int xx, int yy){
  COverlayRGB overlay_cursor(SCREEN_W, SCREEN_H);
  int col_no = (SCREEN_W-xx) >= 7 ? 7: (SCREEN_W-xx);
  int row_no = (SCREEN_H-yy) >= 11 ? 11: (SCREEN_H-yy);
  overlay_cursor.alloc_mem_overlay( col_no, row_no);
  overlay_cursor.copy_overlay( ol_screen, xx, yy);
  overlay_cursor.set_mouse_cursor( 0xff000000);
  overlay_cursor.print_to_display( xx, yy);
}

// Calculate box positions
void calculate_boxes(){
  // left boxes includes: segmentation, object detection and others
  int l_box_w = 260;
  int l_box_h = 100;
  int l_dist = 30;
  for( int i = 0; i < MAX_APP_TYPES; i++){
    box_area[i][0] = rec_area[0][0] + ((rec_area[0][2] - rec_area[0][0])/2 - l_box_w/2);
    box_area[i][1] = rec_area[0][1] + (rec_area[0][3] - rec_area[0][1] - 3*l_box_h - 2*l_dist) / 2
        + i*(l_box_h + l_dist);
    box_area[i][2] = box_area[i][0] + l_box_w;
    box_area[i][3] = box_area[i][1] + l_box_h;
  }

  // right boxes includes app names
  int r_box_w = 300;
  int r_box_h = 100;
  int r_dist_x = 30;
  int r_dist_y = 30;
  for( int i = 3; i < 9; i++){
    box_area[i][0] = rec_area[1][0] + (rec_area[1][2] - rec_area[1][0] - 2*r_box_w - r_dist_x)/2;
    if ((i == 4) || (i == 6) || (i == 8)) box_area[i][0] += (r_box_w + r_dist_x);
    box_area[i][1] = rec_area[1][1] + (rec_area[1][3] - rec_area[1][1] - 3*r_box_h - 2*r_dist_y)/2;
    if ((i == 5) || (i == 6)) box_area[i][1] += (r_box_h + r_dist_y);
    if ((i == 7) || (i == 8)) box_area[i][1] += 2*(r_box_h + r_dist_y);
    box_area[i][2] = box_area[i][0] + r_box_w;
    box_area[i][3] = box_area[i][1] + r_box_h;
  }

  // two boxes for scrolling btw right box's pages
  int scr_box_w = 60;
  int scr_box_h = 25;
  int side_dist = 20;
  int bot_dist = 5;
  for( int i = 9; i < 11; i++){
    box_area[i][0] = rec_area[1][0] + side_dist;
    if( i == 10)
      box_area[i][0] = rec_area[1][2] - side_dist - scr_box_w;
    box_area[i][1] = rec_area[1][3] - bot_dist - scr_box_h;
    box_area[i][2] = box_area[i][0] + scr_box_w;
    box_area[i][3] = box_area[i][1] + scr_box_h;
  }

  // two boxes for scrolling up and down left box's pages
  for( int i = 11; i < 13; i++){
    box_area[i][0] = rec_area[0][0] + side_dist;
    if( i == 12)
      box_area[i][0] = rec_area[0][2] - side_dist - scr_box_w;
    box_area[i][1] = rec_area[0][3] - bot_dist - scr_box_h;
    box_area[i][2] = box_area[i][0] + scr_box_w;
    box_area[i][3] = box_area[i][1] + scr_box_h;
  }
}

//Design background
void bg_on_draw(){
  //bg_overlay.set_background_to_color( 0xFFFFFFFF);
  bg_overlay.load_ppm_img( "bgImage4UI");

  // Print the title to screen
  string text = "FPGA DEMONSTRATION";

  int text_size = 35;
  bg_overlay.draw_ctrlBox_with_fonts( 300-1, 20-1, SCREEN_W-300-1, 120-1,
			0xFFFFFFFF,  0xFFFFFFFF, font_file, text, text_size, 0xFF000000, 0);

  // Draw 2 biggest boxes
  int bb_color = 0xFFD4D2D2; //0xFFF3F6CE
  bg_overlay.draw_ctrlBox_with_fonts( rec_area[0][0], rec_area[0][1], rec_area[0][2], rec_area[0][3],
	  bb_color, bb_color, font_file, "", 0, 0xFFFFFFFF, 5);
  int boxname_w = 150;
  int boxname_h = 30;
  int bName_color = DMP_COLOR;
  int x_name_box = rec_area[0][0] + ( rec_area[0][2] - rec_area[0][0])/2 - boxname_w/2;
  int y_name_box = rec_area[0][1] - boxname_h/2;
  bg_overlay.draw_ctrlBox_with_fonts( x_name_box, y_name_box, x_name_box + boxname_w, y_name_box + boxname_h,
		  bName_color, bName_color, font_file, "CLASSIFICATION", 10, 0xFF000000, 2);

  bg_overlay.draw_ctrlBox_with_fonts( rec_area[1][0], rec_area[1][1], rec_area[1][2], rec_area[1][3],
	  bb_color, bb_color, font_file, "", 0, 0xFFFFFFFF, 5);
  x_name_box = rec_area[1][0] + ( rec_area[1][2] - rec_area[1][0])/2 - boxname_w/2;
  y_name_box = rec_area[1][1] - boxname_h/2;
  bg_overlay.draw_ctrlBox_with_fonts( x_name_box, y_name_box, x_name_box + boxname_w, y_name_box + boxname_h,
		  bName_color, bName_color, font_file, "APPLICATION", 10, 0xFF000000, 2);

  //Draw quit button
  bg_overlay.draw_ctrlBox_with_fonts( 1260-1, 0, 1280-1, 20-1,
  	  bb_color, bb_color, font_file, "X", 10, 0xFF000000, 0);
  //Write DMP website
  bg_overlay.draw_ctrlBox_with_fonts( 900, 680-1, 1280-1, 720-1,
		  0xFFFFFFFF, 0xFFFFFFFF, font_file, "https://www.dmprof.com", 14, 0xFF000000, 2);
}

// Draw boxes
void boxes_on_draw( COverlayRGB &ol_boxes){

  if( st_changed == true){
	ol_boxes.copy_overlay(bg_overlay, 0, 0);

	// Draw boxes inside left big box
	int tApp_available = 0;
	for (int i = 0; i < MAX_APP_TYPES; i++){
		if( app_type[i].amount > 0){
		  tApp_available++;
		}
	}
	// Considering which app types will be showed on the left big box
	int leftover = tApp_available - 3*l_next_page;
	lboxes_will_draw = ( leftover > 3) ? 3 : leftover;

	for (int i = 0; i < lboxes_will_draw; i++){
	  string txt;
	  txt = app_type[i+3*l_next_page].type_name;
	  transform(txt.begin(), txt.end(), txt.begin(), ::toupper);

	  int bg_color = 0xFFFFFFFF; //0xFF0D97D2
	  int otl_color = ( i == (screen_mode - 3*l_next_page)) ? DMP_COLOR: bg_color;
	  ol_boxes.draw_ctrlBox_with_fonts( box_area[i][0], box_area[i][1], box_area[i][2], box_area[i][3],
		  bg_color, otl_color, font_file, txt, 17, 0xFF000000, 5);
	}
	// Draw two button for up and down pages inside left boxes
	if( l_next_page > 0){
	  up_bt_ready = true;
	  int bg_color = 0xFFF1F9BC;
	  int otl_color = 0xFFACAEAF;
	  ol_boxes.draw_ctrlBox_with_fonts( box_area[11][0], box_area[11][1], box_area[11][2], box_area[11][3],
		  bg_color, otl_color, font_file, "<<", 12, 0xFF000000, 3);
	}
	else{
	  down_bt_ready = false;
	}
	if( leftover > 3){
	  down_bt_ready = true;
	  int bg_color = 0xFFF1F9BC;
	  int otl_color = 0xFFACAEAF;
	  ol_boxes.draw_ctrlBox_with_fonts( box_area[12][0], box_area[12][1], box_area[12][2], box_area[12][3],
		  bg_color, otl_color, font_file, ">>", 12, 0xFF000000, 3);
	}
	else{
	  down_bt_ready = false;
	}

	// Considering which apps will be showed on the right big box
	leftover = app_type[ screen_mode].amount - 6*next_page;
	rboxes_will_draw = ( leftover > 6) ? 6 : leftover;

	// Display boxes on the right big box
	for( int i = 0; i < rboxes_will_draw; i++){
	  int bg_color = 0xFFFFFFFF;
	  int otl_color = ( app_type[ screen_mode].app_num[i+6*next_page].is_cam == "true") ? DMP_COLOR: bg_color;
	  ol_boxes.draw_ctrlBox_with_fonts( box_area[3+i][0], box_area[3+i][1], box_area[3+i][2], box_area[3+i][3],
		  bg_color, otl_color, font_file, app_type[screen_mode].app_num[i+6*next_page].name, 17, 0xFF000000, 5);
	}

	// Draw two button for back and next pages inside right boxes
	if( next_page > 0){
	  previous_bt_ready = true;
	  int bg_color = 0xFFF1F9BC;
	  int otl_color = 0xFFACAEAF;
	  ol_boxes.draw_ctrlBox_with_fonts( box_area[9][0], box_area[9][1], box_area[9][2], box_area[9][3],
		  bg_color, otl_color, font_file, "<<", 12, 0xFF000000, 3);
	}
	else{
	  previous_bt_ready = false;
	}
	if( leftover > 6){
	  next_bt_ready = true;
	  int bg_color = 0xFFF1F9BC;
	  int otl_color = 0xFFACAEAF;
	  ol_boxes.draw_ctrlBox_with_fonts( box_area[10][0], box_area[10][1], box_area[10][2], box_area[10][3],
		  bg_color, otl_color, font_file, ">>", 12, 0xFF000000, 3);
	}
	else{
	  next_bt_ready = false;
	}

	st_changed = false;
  }
  // Print to display buffer
  ol_boxes.print_to_display(0, 0);

}

// Update screen display
void screen_update(){

  boxes_on_draw( boxes_overlay);
  draw_cursor_to_display( boxes_overlay, m_cur.cur.x, m_cur.cur.y);
  dmp::util::swap_buffer();
}

// Check which box that mouse pressed
int pressed_area( mouse_infor m){
  int cs = -1;
  for (int i = 0; i < MAX_BOXES; i++){
    if(( m.cur.x >= box_area[i][0]) && ( m.cur.x <= box_area[i][2])
        && ( m.cur.y >= box_area[i][1]) && ( m.cur.y <= box_area[i][3])){
      cs = i;
      break;
    }
  }
  return cs;
}

void *hwacc_thread_func(void *targ) {
  while (true) {
    if (flag == false){
      usleep(20000);  // sleep 1 us
      flag = true;
    }
  }
  return NULL;  // will never reach here but this removes compiler warning...
}

// Main function
int main(int argc, char **argv) {

  if (!dmp::util::init_fb()) {
	fprintf(stderr, "dmp::util::init_fb() failed\n");
	return 1;
  }

  // Read apps from ini file
  if( get_apps_infor() == -1){
	  fprintf(stderr, "No application is read from appList.ini!\n" );
	  return 0;
  }

  // Initialize Mouse and DMP Modules
  mouse_init(m_cur, 0, 0);

  // Set overlay for background
  bg_overlay.alloc_mem_overlay(SCREEN_W, SCREEN_H);
  boxes_overlay.alloc_mem_overlay(SCREEN_W, SCREEN_H);
  bg_on_draw();

  // Calculate dimensions and positions of control boxes
  calculate_boxes();
  screen_mode = 0;

  // Draw boxes to background
  st_changed = true;
  screen_update();

  // Thread for setting up screen reload time and checking stopping signal from buttons
  pthread_t hwacc_thread;
  pthread_create( &hwacc_thread, NULL, hwacc_thread_func, NULL);

  // Set mouse event
  char event[] = "/dev/input/event1";
  set_mouse_event( event);

  // Open mouse event
  if (mouse_open() == EXIT_FAILURE) return 0;

  bool l_just_pressed = false;
  bool m_just_pressed = false;

  int pressed_zone = 0;
  int capture_no = 0;
  while (exit_code == false){
    mouse_read(m_cur);
    if (flag == true){
      screen_update();
      flag = false;
      usleep(50);
    }
    if (m_cur.l_pressed == true){
      l_just_pressed = true;
    }

    if( (m_cur.l_pressed == false) && (l_just_pressed == true)) {
      l_just_pressed = false;
      if( (m_cur.cur.x >= 1260) && (m_cur.cur.y < 20))  exit_code = true;

      // Check which boxes are pressed
      pressed_zone = pressed_area( m_cur);

      if( (pressed_zone >= 0) && (pressed_zone < lboxes_will_draw)){   //mouse pressed inside left boxes
	    st_changed = true;
	    screen_mode = pressed_zone + 3*l_next_page;
        next_page = 0;
      }
      else if( (pressed_zone >= 3) && (pressed_zone < rboxes_will_draw + 3)){ // mouse pressed inside 6 big boxes
		SPC_PIPE *p;
		int app_run = pressed_zone - 3 + 6*next_page;
		p = spc_popen( app_type[screen_mode].app_num[app_run].bin_address.c_str(), NULL, NULL);

		spc_pclose( p);
		usleep(50);

		//Re-update the screen
		st_changed = true;
        screen_update();
        usleep(50);
      }
      else if ( (pressed_zone == 9) && ( previous_bt_ready == true)){ // Previous button is pressed
    	st_changed = true;
        next_page = ( next_page > 0) ? (next_page - 1) : 0;
      }
      else if ((pressed_zone == 10)  && ( next_bt_ready == true)){ // Next button is pressed
	    st_changed = true;
	    next_page++;
      }
      else if ( (pressed_zone == 11) && ( up_bt_ready == true)){ // Previous button is pressed
		st_changed = true;
	    l_next_page = ( l_next_page > 0) ? (l_next_page - 1) : 0;
	    //pick the uper box as defaut mode
	    screen_mode = 3*l_next_page;
	  }
	  else if ((pressed_zone == 12)  && ( down_bt_ready == true)){ // Next button is pressed
	    st_changed = true;
	    l_next_page++;
	    //pick the uper box as defaut mode
	    screen_mode = 3*l_next_page;
	  }
      else{
      }
    }

	if( (m_cur.m_pressed == true) && (m_just_pressed == false)){
	  m_just_pressed = true;
	}

	if (( m_cur.m_pressed == false) && ( m_just_pressed == true)){
	  fprintf(stderr, "Captured!\n" );
	  string txt = "pic_" + to_string( capture_no);
	  capture_no++;
	  boxes_overlay.save_as_ppm_img( txt);
	  m_just_pressed = false;
	}

  } // end while

  mouse_close();
  dmp::util::shutdown();

  return 0;
}
