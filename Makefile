SUBDIRS = common/src \
	dv700/src \
	CaffeGoogLeNet \
	CaffeMobileNet \
	CaffeSqueezeNet \
	KerasGoogLeNet \
	KerasMobileNet \
	KerasSqueezeNet \
	CaffeGoogLeNetCam \
	TinyYolo \
	SSDFacePerson \
	test_monodepth

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
