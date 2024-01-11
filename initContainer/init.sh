#!/bin/bash

iptables -t nat -A PREROUTING -p tcp --dport 80 -j REDIRECT --to-port 10096
iptables -t nat -A OUTPUT -p tcp --dport 80 -m owner ! --uid-owner 1005 -j DNAT --to 127.0.0.1:10096
#iptables -t nat -A OUTPUT -p tcp --dport 80 -m owner ! --uid-owner 1005 -j REDIRECT --to-port 10096

# List all iptables rules.
iptables -t nat --list
