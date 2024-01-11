#!/bin/bash

#DAEMON_IP="20.15.10.220"

# receive attestation and subject hash as input
ATTESTATION_HASH=$1
SUBJECT_HASH=$2

# $DAEMON_IP fetched from the environment
timeStart=$(date +%s%3N)
ATTESTER_HASH=$(/etc/wave/wv --agent $DAEMON_IP:777 inspect vnf.ent | grep Hash | awk '{print $2}')

/etc/wave/wv --agent $DAEMON_IP:777 resolve $ATTESTATION_HASH --perspective vnf.ent --passphrase "pass123" > "verifyOut.txt"

ifAtt=$(cat verifyOut.txt | grep "= Attestation")

if [[ -z "$ifAtt" ]]
then
    echo -e "0" > "logVerification.txt"
else
    subject=$(cat verifyOut.txt | grep "Subject:" | awk '{print $2}')
    attester=$(cat verifyOut.txt | grep "Attester:" | awk '{print $2}')
    if [[ "$subject" == "$SUBJECT_HASH" && "$attester" == "$ATTESTER_HASH" ]]
    then
        echo -e "1" > "logVerification.txt"
    else
        echo -e "0" > "logVerification.txt"
    fi
fi
timeEnd=$(date +%s%3N)
timeDiff=$(($timeEnd-$timeStart))
echo -e "Verification $timeDiff\n"
