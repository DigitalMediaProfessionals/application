SUBDIRS = common/src \
	KerasGoogLeNet \
	# CaffeGoogLeNetCam \
	# CaffeGoogLeNet \
	# CaffeMobileNet \
	# CaffeSqueezeNet
	# KerasMobileNet \
	# KerasSqueezeNet \
	# YOLOv3Camera \
	# YOLOv3 \
	# SegNetBasic \	
	# CaffeSqueezeNet \
	
	
	
	
	

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
