#!/bin/bash

DAEMON_IP="20.15.10.220"
proofsDir="proofs/"

# receive attester and permissions hash as an input
ATTESTER_HASH=$1
PERMISSIONS_HASH=$2
    
SUBJECT_HASH=$(/etc/wave/wv --agent $DAEMON_IP:777 inspect vnf.ent | grep Hash | awk '{print $2}')

/etc/wave/wv --agent $DAEMON_IP:777 rtprove --subject vnf.ent --passphrase "pass123" ${PERMISSIONS_HASH}:read@${ATTESTER_HASH}/* 

cp "proof-Subject-${SUBJECT_HASH}-Attester-${ATTESTER_HASH}.pem" "$proofsDir"
