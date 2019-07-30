# YOLOv3TF

## Syntax
```
$ ./YOLOv3TF.py --image-dir {image_path} --model-path {model_path}
```

* default image_path : ../bin/images_yolo/
* default model_path : ../model/yolov3-tiny.h5

## YOLOv3TF

YOLOv3-tiny demo application run in Tensorflow.
Will process all images in `{image_path}` and output the results
with labeled bounding box to `output/` folder.