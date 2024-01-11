#!/usr/bin/python3
import csv
import numpy as np
import pandas as pd
import os

# creates lists for each of the files in alltables/(no)wave/ then returns files
def create_lists():
    wave_array = [[] for _ in range(14)]
    nowave_array = [[] for _ in range(14)]
    verify_array = [[] for _ in range(14)]
    for i in range(1, 21):
        wave_file = ("alltables/wave/tables%s.csv" % i)
        nowave_file = ("alltables/nowave/tables%s.csv" % i)
        with open(wave_file, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            # tmp_array_1 = []
            # tmp_array_2 = []
            for row in reader:
                cur = int(row['id']) - 1
                cur_time = row['time']
                verify_time = row['verify']
                # tmp_array_1.append(cur_time)
                # tmp_array_2.append(verify_time)
                wave_array[cur].append(int(cur_time))
                verify_array[cur].append(int(verify_time))
        with open(nowave_file, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            # tmp_array_3 = []
            for row in reader:
                cur = int(row['id']) - 1
                cur_time = row['time']
                # tmp_array.append(cur_time)
                nowave_array[cur].append(int(cur_time))
    return wave_array, nowave_array, verify_array


# reads file to dataframe, inserts new column with the mean. returns dataframe
def read_file_to_dataframe(averages ,file):
    df = pd.read_csv(file)
    final_df = pd.concat([df, averages], axis=1, join="inner")
    return final_df


def main():
    folder = os.getcwd()

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

    req = ["AMF->NRF(PUT)", "SMF->NRF(POST)", "SMF->NRF(PUT)", "AMF->AUSF(POST)", \
            "AUSF->UDM(POST)", "UDM->UDR(GET)", "UDM->UDR(PATCH)", "AMF->AUSF(PUT)", \
            "AUSF->UDM(POST)", "UDM->UDR(GET)", "UDM->UDR(PUT)", "AMF->SMF(POST)", \
            "SMF->AMF(POST)", "AMF->SMF(POST)"]

    # create lists for mean
    wave_array, nowave_array, verify_array = create_lists()
    wave_averages_table = [None] * 14
    wave_std_table = [None] * 14
    nowave_averages_table = [None] * 14
    nowave_std_table = [None] * 14
    verify_averages_table = [None] * 14

    for i in range(0, 14):
        wave_averages_table[i] = np.mean(wave_array[i])
        wave_std_table[i] = np.std(wave_array[i])
        nowave_averages_table[i] = np.mean(nowave_array[i])
        nowave_std_table[i] = np.std(nowave_array[i])
        verify_averages_table[i] = np.mean(verify_array[i])

    # transform tables into dataframes, and dataframes into csv, then creates file of means
    # wave_averages = pd.DataFrame(wave_averages_table, columns=['mean-wave'])
    # nowave_averages = pd.DataFrame(nowave_averages_table, columns=['mean-nowave'])
    # wave_csv_file = folder + '/wave_mean.csv'
    # nowave_csv_file = folder + '/no_wave_mean.csv'
    # wave_averages.to_csv(wave_csv_file)
    # nowave_averages.to_csv(nowave_csv_file)
    final_df = pd.DataFrame(list(zip(req,verify_averages_table, wave_averages_table, wave_std_table, nowave_averages_table, nowave_std_table)), \
                columns=['Request','verify', 'wave','wave-std','nowave','nowave-std'])
    final_csv_file = folder + '/all_means.csv'
    final_df.to_csv(final_csv_file)

    # creates a new dataframe and file to include mean
    # for i in range(1, 20):
        # current_wave_file = ('/alltables/wave/tables%s.csv' % i)
        # current_nowave_file = ('/alltables/nowave/tables%s.csv' % i)

        # new_wave_df = read_file_to_dataframe(wave_averages, folder + current_wave_file)
        # new_nowave_df = read_file_to_dataframe(nowave_averages, folder + current_nowave_file)

        # wave_csv_file = folder + ('/alltables/wavemean/tables%i.csv' % i)
        # nowave_csv_file = folder + ('/alltables/nowavemean/tables%i.csv' % i)

        # new_wave_df.to_csv(wave_csv_file)
        # new_nowave_df.to_csv(nowave_csv_file)


main()
