#!/bin/bash

wavescp_version="releaseV1.4"
rpscp_version="wave-1"
initscp_version="v2.0"

nrf_version="v2.0"
udr_version="v1.0"
udm_version="v1.2"
ausf_version="v1.2"
amf_version="v2.0"
smf_version="v1.2"
upf_version="bench"
gnbsim_version="n4kul"
dnn_version="4kaggrdu"

wavescpimage="pragyasharmaa/wavescp"
rpscpimage="pragyasharmaa/redirectproxyscp"
initscpimage="pragyasharmaa/initscp"

nrfimage="pragyasharmaa/oai-nrf"
udrimage="pragyasharmaa/oai-udr"
udmimage="pragyasharmaa/oai-udm"
ausfimage="pragyasharmaa/oai-ausf"
amfimage="pragyasharmaa/oai-amf"
smfimage="pragyasharmaa/oai-smf"
upfimage="tolgaomeratalay/upf"
gnbsimimage="tolgaomeratalay/gnbsim"
dnnimage="tolgaomeratalay/oai-dnn"

nodes=( "192.168.2.95" "192.168.2.87" "192.168.2.86" "192.168.2.82" "192.168.2.68" "192.168.2.57" "192.168.2.63" "192.168.2.54" "192.168.2.48" "192.168.2.50" "192.168.2.45" )

for i in "${nodes[@]}"
do
    ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $wavescpimage:$wavescp_version 
    sleep 5
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $rpscpimage:$rpscp_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $initscpimage:$initscp_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $nrfimage:$nrf_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $udrimage:$udr_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $udmimage:$udm_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $ausfimage:$ausf_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $amfimage:$amf_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $smfimage:$smf_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $upfimage:$upf_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $gnbsimimage:$gnbsim_version 
    #ssh -i ~/.ssh/key.pem ubuntu@$i sudo docker image pull $dnnimage:$dnn_version 
done



