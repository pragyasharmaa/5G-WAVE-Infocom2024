#!/bin/bash

NAMESPACE="oai"

wrnmsg()
{
    local message="$1"
    local bold=$(tput bold)
    local normal=$(tput sgr0)

    local color=$(tput setaf 4)
    local color_default=$(tput setaf 9)

    echo -en "${bold}${color}${message}${color_default}${normal}"
}

waitAllPods()
{
    wrnmsg "\tWaiting for all pods to be deployed"

    while [[ "$(kubectl get pods -n ${NAMESPACE} --field-selector status.phase!=Running -o name)" != "" ]];
    do
        wrnmsg "."
        sleep 2
    done

    while [[ "$(kubectl get pods -n ${NAMESPACE} | grep 'Error\|CrashLoopBackOff' )" != "" ]];
    do
        wrnmsg "."
        sleep 2
    done
    echo ""
}

kubectl apply -f 02_waveps.yaml -n $NAMESPACE
waitAllPods
sleep 5


kubectl apply -f 03_waved.yaml -n $NAMESPACE
waitAllPods
sleep 5

kubectl apply -k . 
