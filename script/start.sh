#!/bin/bash
DATA_DIR="/root/Data/data/"

ProJ="csob-docker"
ProJN="csob-docker"
ImageName="mhdj/csob:v2.0"
YamlName="./yaml/csob_job.yaml"

DataFolders=`ls ${DATA_DIR}`
Dir="/nfs/data/"


# 获取所有data目录下的数据目录
i=1
set=()
for j in ${DataFolders}
do
    set[$i]=${j}
    i=$i+1
done


tot=()
k=1;
for i in ${set[*]} 
do
    # echo ${i}
    folder=`ls ${DATA_DIR}${i}`
    # echo ${#folder[*]}
    for j in ${folder}
    do
        tot[$k]=${Dir}${i}'/'${j}
        k=$k+1
    done
done 

w = 1



export ImageName=${ImageName}

for i in ${tot[*]}
do
    if [[ $w -ne 3 ]];
    then
        ((w+=1))

        export ProJ="${ProJN}${w}"
        echo ${ProJ}
        export FileName=${i}
        envsubst < ${YamlName} | kubectl create -f -
    else
        break 
    fi
done


