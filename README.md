# Dawnbench Imagenet Inference

## Summary
This is an imagenet classification benchmark on HIE,an inference framework developed by heterogeneous computing intelligence team(HCI),the model was improved by offline version intelligence team,both from DAMO Academy,AliCloud.

## Performance
top1 : 0.75794<br />
top5 : 0.93004<br />
latency : 0.4331 ms

## Enviroment
CPU : Intel(R) Xeon(R) Platinum 8163 CPU @ 2.50GHz<br />
GPU : Tesla T4
OS : gcc version 4.8.5 20150623 (Red Hat 4.8.5-4) (GCC)

## Dependencies
cuda10.0<br />
cudnn-7.5.0<br />
Protobuf-3.6.1<br />
Anaconda Python-3.7.4 (Python3 && PIL for image preprocess)

## Usage

1 install dependencies above,set environment variables like PYTHONHOME<br />

2 clone this repo,suppose your current absolute working path is ${CURDIR}<br />

3 link ${CURDIR}/data/ILSVRC2012_img_val to imagenet dataset path<br />

4 export LD_LIBRARY_PATH=${CURDIR}/third_party_libs:${LD_LIBRARY_PATH}

5 sh build.sh<br />

6 sh set_env.sh<br />

7 ./build/bin/infer ./data/model.hie ./data/ILSVRC2012_img_val ./data/ILSVRC2012_labels.txt
