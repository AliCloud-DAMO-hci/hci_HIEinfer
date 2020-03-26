# Dawnbench Imagenet Inference

## Summary
An imagenet classification benchmark on HIE engine.

HIE (with falcon compute library) is a high-performance DL inference framework self-developed by Heterogeneous Computing Intelligence(HCI) team in Alibaba Cloud.

The model was improved by Machine Intelligence Visual Technology(MIVT) team in Alibaba Cloud.

## Performance
```
top1 accuracy : 0.76376
top5 accuracy : 0.93114
latency per image : 0.3121
```

## Enviroment
ECS type instance ecs.gn6i-c8g1.2xlarge on Alibaba Cloud

Ref : https://www.alibabacloud.com/help/doc-detail/25378.htm
```
CPU : Intel(R) Xeon(R) Platinum 8163 CPU @ 2.50GHz
GPU : Nvidia Tesla T4
OS : Linux version 3.10.0-514.26.2.el7.x86_64 (gcc version 4.8.5 20150623 (Red Hat 4.8.5-11) (GCC) )
```

## Dependencies
```
cmake-3.8 or higher
cuda-10.0
Protobuf-3.6.1
Anaconda Python-3.7.4 (Python3 && PIL for image preprocess)
```


## Usage
1 install dependencies above,set environment variables like PYTHONHOME,LD_LIBRARY_PATH

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
sh ./set_env.sh (make sure sudo privilege)
./build/bin/infer ./data/MIVTNET-v3.hie ./data/ILSVRC2012_img_val ./data/ILSVRC2012_labels.txt
```
