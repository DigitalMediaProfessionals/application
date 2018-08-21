SUBDIRS = common/src \
	CaffeGoogLeNet \
	CaffeMobileNet \
	CaffeSqueezeNet

MOREDIRS = CaffeGoogLeNetCam \
	KerasGoogLeNet \
	KerasMobileNet \
	KerasSqueezeNet \
	SegNetBasic \
	YOLOv3 \
	YOLOv3Camera

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
