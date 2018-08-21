SUBDIRS = common/src \
	CaffeGoogLeNet \
	CaffeMobileNet \
	CaffeSqueezeNet \
	KerasMobileNet \
	KerasSqueezeNet \
	SegNetBasic \
	YOLOv3 \
	YOLOv3Camera

MOREDIRS = CaffeGoogLeNetCam \
	KerasGoogLeNet \
	

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
