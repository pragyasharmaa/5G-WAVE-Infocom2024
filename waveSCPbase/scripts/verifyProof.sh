#!/bin/bash

DAEMON_IP="20.15.10.220"
proofsDir="proofs"

PROOF_NAME="$1"

/etc/wave/wv --agent $DAEMON_IP:777 verify "$proofsDir/${PROOF_NAME}" > "verifyOutput.txt"

subject=$(cat verifyOutput.txt | grep "Subject:" | awk '{print $2}')
attester=$(cat verifyOutput.txt | grep "Namespace:" | awk '{print $2}')

echo -e $subject > "logVerification.txt"
echo -e $attester >> "logVerification.txt"
