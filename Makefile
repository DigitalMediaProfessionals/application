SUBDIRS = common/src \
	MouseDemo \
	CaffeMobileNet \
	CaffeSqueezeNet \
	KerasMobileNet \
	KerasSqueezeNet \
	SegNetBasic \
	DeconvNetBasic \
	YOLOv3 \
	YOLOv3Camera \
	YOLOv3Pywrap \
	KerasDepthMap \
	JointFace

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
done
