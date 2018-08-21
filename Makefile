SUBDIRS = common/src \
	CaffeGoogLeNet \
	CaffeMobileNet \
	CaffeSqueezeNet \
	SegNetBasic \
	YOLOv3

MOREDIRS = CaffeGoogLeNetCam \
	KerasGoogLeNet \
	KerasMobileNet \
	KerasSqueezeNet \
	YOLOv3Camera

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
