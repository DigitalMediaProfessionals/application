SUBDIRS = common/src \
	CaffeGoogLeNet \
	CaffeMobileNet \
	CaffeSqueezeNet \
	KerasGoogLeNet \
	KerasMobileNet \
	KerasSqueezeNet \
	SegNetBasic \
	YOLOv3 \
	YOLOv3Camera

MOREDIRS = CaffeGoogLeNetCam

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
