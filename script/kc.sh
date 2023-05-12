#!/bin/bash

# kubectl 命令的快捷操作

function kp(){

kubectl get pod
}

function kd(){

kubectl get deployments
}

function kdp(){
    kubectl delete pod $2
}

function kdd(){
    kubectl delete deployments $1
}

function kl(){
    kubectl logs $1
}


if [ $1 == "kp" ];then
   kp
fi

if [ $1 == "kd" ]
then
    kd
fi

if [ $1 == "kdp" ]
then
    kdp $2
fi

if [ $1 == "kdd" ]
then
    kdd $2
fi

if [ $1 == "kl" ]
then
    kl $2
fi