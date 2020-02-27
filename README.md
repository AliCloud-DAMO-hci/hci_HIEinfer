# Dawnbench Imagenet Inference

## Summary
This is an imagenet classification benchmark on HIE,an inference framework self-developed by Heterogeneous Computing Intelligence(HCI) team in Alibaba Cloud.
The model was improved by Machine Intelligence Visual Technology(MIVT) team in Alibaba Cloud.

## Performance
```
top1 : 0.75794
top5 : 0.93004
latency : 
```

## Enviroment
```
CPU : 
GPU :
OS :
```

## Dependencies
```
cuda-10.0
cudnn-7.5.0
Protobuf-3.6.1
Anaconda Python-3.7.4 (Python3 && PIL for image preprocess)
```


## Usage
1 install dependencies above,set environment variables like PYTHONHOME

2 clone this repo,suppose your current absolute working path is ${CURDIR}

3 link ./data/ILSVRC2012_img_val to imagenet dataset path
```
./data/ILSVRC2012_img_val
├── ILSVRC2012_val_00000001.JPEG
├── ILSVRC2012_val_00000002.JPEG
├── ILSVRC2012_val_00000003.JPEG
├── ILSVRC2012_val_00000004.JPEG
├── ILSVRC2012_val_00000005.JPEG
├── ILSVRC2012_val_00000006.JPEG
```

then
```
export LD_LIBRARY_PATH=${CURDIR}/third_party_libs:${LD_LIBRARY_PATH}
sh ./build.sh
sh ./set_env.sh
./build/bin/infer ./data/MIVT-NET.hie ./data/ILSVRC2012_img_val ./data/ILSVRC2012_labels.txt
```
