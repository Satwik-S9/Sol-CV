#! usr/bin/bash

ROOT=$(pwd)
DATASET=${ROOT}/dataset.yaml
runTraining() {
    echo "Choosing Datset from config file dataset.yml at ..."
    echo -n "    $DATASET"
    cd yolov5 && python train.py --img 320 --batch 16 --epochs 100 --data ${DATASET} --weights yolov5m.pt --workers 2
}

if [[ -d "yolov5" && ! -L "yolov5" ]] ; then
    runTraining
else
    printf "\nDo you want to clone the folder [Y/n]  "
    read RESPONSE
    if [[ "$RESPONSE" -eq "Y" || "$RESPONSE" -eq "y" ]]; then
        echo "Cloning the repo ..."
        git clone https://github.com/ultralytics/yolov5
    else
        echo "Clone the repo from https://github.com/ultralytics/yolov5"
        exit
    fi
    runTraining
fi
# 