#!/bin/bash

#DAEMON_IP="20.15.10.220"

# receive subject hash as an input
SUBJECT_HASH=$1
LOG_HASH_PERM="hash-permissions.txt"
LOG_HASH_ATT="hash-att.txt"
    
# create a new permissions ent for each auth request
# $DAEMON_IP fetched from the environment
/etc/wave/wv --agent $DAEMON_IP:777 mke -o permissions.ent --nopassphrase > "perm.txt"
PERMISSIONS_HASH=$(/etc/wave/wv --agent $DAEMON_IP:777 inspect permissions.ent | grep Hash | awk '{print $2}')
echo -e $PERMISSIONS_HASH > "$LOG_HASH_PERM"

# $DAEMON_IP fetched from the environment
/etc/wave/wv --agent $DAEMON_IP:777 rtgrant --attester vnf.ent --indirections 1  --passphrase "pass123" --subject ${SUBJECT_HASH} ${PERMISSIONS_HASH}:read@vnf.ent/* > "createOutput.txt"

attfilename=$(cat createOutput.txt | grep "wrote attestation:" | awk '{print $3}')
attHash=$(/etc/wave/wv --agent $DAEMON_IP:777 inspect $attfilename | grep Hash | awk '{print $3}')
time_taken=$(cat createOutput.txt | grep "Total time" | awk '{print $6}')
echo -e $attHash > "$LOG_HASH_ATT"
echo -e "Attestation $time_taken\n"

