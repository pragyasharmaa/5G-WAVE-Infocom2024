#!/bin/bash

#DAEMON_IP="20.15.10.220"

LOG_HASH_ENT="hash-ent.txt"

# $DAEMON_IP fetched from the environment
/etc/wave/wv --agent $DAEMON_IP:777 mke -o vnf.ent --nopassphrase > "entOut.txt"
entHash=$(/etc/wave/wv --agent $DAEMON_IP:777 inspect vnf.ent | grep Hash | awk '{print $2}')
time_taken=$(cat entOut.txt | grep "actionMkEntity" | awk '{print $7}')
echo -e $entHash > "$LOG_HASH_ENT"
echo -e "Entity $time_taken"

