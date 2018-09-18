SUBDIRS = common/src \
	SegNetBasic \
	CaffeGoogLeNet \
	CaffeGoogLeNetCam \
	CaffeMobileNet \
	CaffeSqueezeNet \
	KerasGoogLeNet \
	KerasMobileNet \
	KerasSqueezeNet \
	YOLOv3Camera \
	YOLOv3
	# cnn \
	# cat \
	# segnet \
	

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
done