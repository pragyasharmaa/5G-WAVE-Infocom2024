#!/bin/bash

folder=$1

numSubSlices=$2
if [ -z "$numSubSlices" ]
then
    numSubSlices=1
fi

repmod=100
nrfc=10
amfc=10
supfc1=10
supfc2=40
gnbsimc=10
gnbsims=10

dir="deplogs/$folder"

nrfpod=$(kubectl get pods -n oai  | grep nrf$nrfc | awk '{print $1}')
nrfnet1IP=$(kubectl exec -n oai $nrfpod -c nrf -- ifconfig | grep "inet 10.100" | awk '{print $2}')
udrpod=$(kubectl get pods -n oai  | grep udr$nrfc | awk '{print $1}')
udrnet1IP=$(kubectl exec -n oai $udrpod -c udr -- ifconfig | grep "inet 10.100" | awk '{print $2}')
udmpod=$(kubectl get pods -n oai  | grep udm$nrfc | awk '{print $1}')
udmnet1IP=$(kubectl exec -n oai $udmpod -c udm -- ifconfig | grep "inet 10.100" | awk '{print $2}')
ausfpod=$(kubectl get pods -n oai  | grep ausf$nrfc | awk '{print $1}')
ausfnet1IP=$(kubectl exec -n oai $ausfpod -c ausf -- ifconfig | grep "inet 10.100" | awk '{print $2}')

# collect logs from rpscp

echo -e $nrfnet1IP > $dir/nrf$nrfc-rp.log
kubectl logs -n oai $nrfpod -c rpscp >> $dir/nrf$nrfc-rp.log
echo -e $udrnet1IP > $dir/udr$nrfc-rp.log
kubectl logs -n oai $udrpod -c rpscp >> $dir/udr$nrfc-rp.log
echo -e $udmnet1IP > $dir/udm$nrfc-rp.log
kubectl logs -n oai $udmpod -c rpscp >> $dir/udm$nrfc-rp.log
echo -e $ausfnet1IP > $dir/ausf$nrfc-rp.log
kubectl logs -n oai $ausfpod -c rpscp >> $dir/ausf$nrfc-rp.log

# collect logs from wavescp
kubectl logs -n oai $nrfpod -c wavescp > $dir/nrf$nrfc-wave.log
kubectl logs -n oai $udrpod -c wavescp > $dir/udr$nrfc-wave.log
kubectl logs -n oai $udmpod -c wavescp > $dir/udm$nrfc-wave.log
kubectl logs -n oai $ausfpod -c wavescp > $dir/ausf$nrfc-wave.log

for ((amf=1;amf<=$numSubSlices;amf++))
do
    amfpod=$(kubectl get pods -n oai  | grep amf$amfc | awk '{print $1}')
	amfnet1IP=$(kubectl exec -n oai $amfpod -c amf -- ifconfig | grep "inet 10.100" | awk '{print $2}')
    smfpod=$(kubectl get pods -n oai  | grep smf$amfc | awk '{print $1}')
	smfnet1IP=$(kubectl exec -n oai $smfpod -c smf -- ifconfig | grep "inet 10.100" | awk '{print $2}')
    upfpod=$(kubectl get pods -n oai  | grep spgwu-tiny$supfc1 | awk '{print $1}')
	gnbsimpod=$(kubectl get pods -n oai  | grep oai-gnbsim$gnbsims | awk '{print $1}')
    
    echo -e $amfnet1IP > $dir/amf$amfc-rp.log
    kubectl logs -n oai $amfpod -c rpscp >> $dir/amf$amfc-rp.log
    echo -e $smfnet1IP > $dir/smf$amfc-rp.log
    kubectl logs -n oai $smfpod -c rpscp >> $dir/smf$amfc-rp.log
    kubectl logs -n oai $amfpod -c wavescp > $dir/amf$amfc-wave.log
    kubectl logs -n oai $smfpod -c wavescp > $dir/smf$amfc-wave.log

	((gnbsims+=1))
    ((amfc+=1))
	((supfc1+=1))
done
