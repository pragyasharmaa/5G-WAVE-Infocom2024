#!/bin/python3

import glob
import pandas as pd
import datetime
import sys

def compute_diff_ms(arrival, departure):
    fmt = '%Y-%m-%d %H:%M:%S,%f'
    arrival_t = datetime.datetime.strptime(arrival, fmt)
    departure_t = datetime.datetime.strptime(departure, fmt)
    time_diff = departure_t - arrival_t
    ms_diff = int(time_diff.total_seconds() * 1000)
    return ms_diff

folder = sys.argv[1]
path = folder + "/*-rp.log"

logFiles = glob.glob(path)

for filename in logFiles:
    vnf_name = filename.split('/')[1].split('.')[0]
    file = open(filename, 'r')
    keys = ['id', 'arrival', 'departure', 'type', 'client', 'host', 'path']

    all_reqs = []
    vnfIP = file.readline().strip()
    for line in file.readlines():
        if 'Request' in line:
            req = {}
            arrival_time = line.split(';')[0].strip()
            req_type = line.split(';')[8].strip()
            req_id = line.split(';')[2].strip()
            client = line.split(';')[4].strip()
            host = line.split(';')[6].strip()
            req_path = line.split(';')[10].strip()
            req['id'] = req_id
            req['arrival'] = arrival_time
            req['type'] = req_type
            req['client'] = client
            req['host'] = host
            req['path'] = req_path
            req['departure'] = ''
            req['diff'] = ''

            if "10.100.17" in client or "10.100.11" in client:
                pass
            else:
                if vnfIP==client: 
                    all_reqs.append(req)

        if 'Response' in line:
            req_id = line.split(';')[2].strip()
            departure_time = line.split(';')[0].strip()
            req = next((d for d in all_reqs if d['id'] == req_id), None)
            if req != None:
                req['departure'] = departure_time
                arrival_time = req['arrival']
                req['diff'] = compute_diff_ms(arrival_time, departure_time)
    
    df_all = pd.DataFrame(all_reqs)
    if not df_all.empty:
        df_min = df_all[['type','client','host','diff']].copy()
        # print(df_min)

        csv_file = folder + '/' + vnf_name + '.csv'  
        df_min.to_csv(csv_file)            

#------------------------------------------------------------------------------------

#------------------------------------------------------------------------------------

path = folder + "/*-rp.csv"
csvFiles = glob.glob(path)
pair_id = 0
table = []

for filename in csvFiles:
    file = open(filename, 'r')

    headers = file.readline()
    for line in file.readlines():
        req = {}
        seqno = line.split(',')[0].strip()
        reqtype = line.split(',')[1].strip()
        client = line.split(',')[2].strip()
        host = line.split(',')[3].strip()
        time = line.split(',')[4].strip()

        if "10.100.11" in client:
            vnf_from = "nrf"
        elif "10.100.12" in client:
            vnf_from = "udr"
        elif "10.100.13" in client:
            vnf_from = "udm"
        elif "10.100.14" in client:
            vnf_from = "ausf"
        elif "10.100.15" in client:
            vnf_from = "amf"
        elif "10.100.16" in client:
            vnf_from = "smf"

        if "10.100.11" in host:
            vnf_to = "nrf"
        elif "10.100.12" in host:
            vnf_to = "udr"
        elif "10.100.13" in host:
            vnf_to = "udm"
        elif "10.100.14" in host:
            vnf_to = "ausf"
        elif "10.100.15" in host:
            vnf_to = "amf"
        elif "10.100.16" in host:
            vnf_to = "smf"

        if vnf_to == "nrf" and reqtype == "PATCH":
            pass
        else:
            req['from'] = vnf_from
            req['to'] = vnf_to
            req['type'] = reqtype
            req['time'] = time
    
            # Create table in order of the unique request ids we have 
            # AMF -> NRF (PUT)      ==> 1
            # SMF -> NRF (POST)     ==> 2
            # SMF -> NRF (PUT)      ==> 3
            # AMF -> AUSF (POST)    ==> 4
            # AUSF -> UDM (POST)    ==> 5
            # UDM -> UDR (GET)      ==> 6
            # UDM -> UDR (PATCH)    ==> 7
            # AMF -> AUSF (PUT)     ==> 8
            # AUSF -> UDM (POST)    ==> 9
            # UDM -> UDR (GET)      ==> 10
            # UDM -> UDR (PUT)      ==> 11
            # AMF -> SMF (POST)     ==> 12
            # SMF -> AMF (POST)     ==> 13
            # AMF -> SMF (POST)     ==> 14

            if vnf_from == "amf" and vnf_to == "nrf":
                req['id'] = 1
            elif vnf_from == "smf" and vnf_to == "nrf":
                if reqtype == "POST":
                    req['id'] = 2
                else:
                    req['id'] = 3
            elif vnf_from == "amf" and vnf_to == "ausf":
                if reqtype == "POST":
                    req['id'] = 4
                else:
                    req['id'] = 8
            elif vnf_from == "ausf" and vnf_to == "udm":
                if int(seqno) == 0:
                    req['id'] = 5
                else:
                    req['id'] = 9
            elif vnf_from == "udm" and vnf_to == "udr":
                if int(seqno) == 0:
                    req['id'] = 6
                elif int(seqno) == 1:
                    req['id'] = 7
                elif int(seqno) == 2:
                    req['id'] = 10
                else:
                    req['id'] = 11
            elif vnf_from == "amf" and vnf_to == "smf":
                if int(seqno) == 3:
                    req['id'] = 12
                else:
                    req['id'] = 14
            elif vnf_from == "smf" and vnf_to == "amf":
                req['id'] = 13


            table.append(req)

df_table = pd.DataFrame(table)
df_table.sort_values('id', inplace=True)
df_table.set_index('id', inplace=True)
# print(df_table)

csv_file = folder + '/' + 'table.csv'  
df_table.to_csv(csv_file)            
