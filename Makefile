SUBDIRS = common/src \
	MouseDemo \
	CaffeGoogLeNet \
	CaffeGoogLeNetCam \
	CaffeMobileNet \
	CaffeSqueezeNet \
	KerasGoogLeNet \
	KerasMobileNet \
	KerasSqueezeNet \
	SegNetBasic \
	YOLOv3 \
	YOLOv3Camera \
	YOLOv3Pywrap

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
done
