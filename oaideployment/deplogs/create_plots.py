#!/bin/python3

# import tkinter
import sys
import numpy as np
import os
import pandas as pd
import matplotlib
# matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import matplotlib.patches as mpatches
import matplotlib.lines as mlines
import seaborn as sns

xkcd_colors = dict(mcolors.XKCD_COLORS)

folder_wave = sys.argv[1]
folder_nowave = sys.argv[2]

fmean = open("mean.txt", 'r')
verify_mean = fmean.readline().strip()
folder = folder_wave
csvpath = folder + "/table.csv"
df = pd.read_csv(csvpath, header=0, index_col=[0])
# print(df)

client_vnfs = ['AMF', 'SMF', 'AUSF', 'UDM']
ax_1_ticks = []
ax_1_ticks.append(0)

# registration times
row_1 = df.loc[(df['from'] == "amf") & (df['to'] == "nrf")]
T1 = 0
Tstart1 = 0
Td_1 = row_1.iloc[0]['time']
ax_1_ticks.append(Td_1)

row_2_3 = df.loc[(df['from'] == "smf") & (df['to'] == "nrf")]
T2 = T1 + 200
ax_1_ticks.append(T2)
Td_2 = row_2_3.iloc[0]['time']
T3 = T2 + Td_2
ax_1_ticks.append(T3)
Td_3 = row_2_3.iloc[1]['time']
ax_1_ticks.append(T3+Td_3)


# 5g aka
row_4_5 = df.loc[(df['from'] == "amf") & (df['to'] == "ausf")]
# T4 = 2000
T4 = T3 + Td_3 + 200
Tstart2 = T4
Td_4 = row_4_5.iloc[0]['time']
T5 = T4 + Td_4 + 0.5
Td_5 = row_4_5.iloc[1]['time']

row_6_7 = df.loc[(df['from'] == "ausf") & (df['to'] == "udm")]
Td_6 = row_6_7.iloc[0]['time']
T6 = T4 - 30 + Td_4 - Td_6   # avg OAI time
Td_7 = row_6_7.iloc[1]['time']
T7 = T5 - 30 + Td_5 - Td_7   # avg OAI time

row_8_9_10_11 = df.loc[(df['from'] == "udm") & (df['to'] == "udr")]
T8 = T6 + int(verify_mean)   # avg wave verification time
Td_8 = row_8_9_10_11.iloc[0]['time']
T9 = T8 + Td_8  
Td_9 = row_8_9_10_11.iloc[1]['time']
T10 = T7 + int(verify_mean)  # avg wave verification time
Td_10 = row_8_9_10_11.iloc[2]['time']
T11 = T10 + Td_10
Td_11 = row_8_9_10_11.iloc[3]['time']


row_12_14 = df.loc[(df['from'] == "amf") & (df['to'] == "smf")]
# T12 = T5 + Td_5 + 500
T12 = T11 + Td_11 + 200
Tstart3 = T12
Td_12 = row_12_14.iloc[0]['time']
row_13 = df.loc[(df['from'] == "smf") & (df['to'] == "amf")]
T13 = T12 + Td_12
Td_13 = row_13.iloc[0]['time']
T14 = T13 + Td_13
Td_14 = row_12_14.iloc[1]['time']


fig_1 = plt.figure(1, figsize=(25,6))
ax_1 = fig_1.subplots()
fig_2 = plt.figure(2, figsize=(10,5)) 
ax_2 = fig_2.subplots()
fig_3 = plt.figure(3, figsize=(10,5)) 
ax_3 = fig_3.subplots()
# ax_1.use_sticky_edges = False
# ax_2.use_sticky_edges = False
# ax_3.use_sticky_edges = False
marker_list = ['P', '^', '*', 'p', 'v', 'o', '>', '*', '2', 'x', '.', 'd', '<', 'h']

bar_width=0.4
bar_1_color=xkcd_colors['xkcd:sky blue']
bar_1_edgecolor=xkcd_colors['xkcd:almost black']
hatch_1_color=xkcd_colors['xkcd:dark grey blue']
marker_color=xkcd_colors['xkcd:dark']
# opacity=0.5
opacity=1
line_width=1
# hatch_width=0.5

ax_1.set_ylim([0,5])
ax_2.set_ylim([0,4])
ax_3.set_ylim([0,3])
plt.rcParams['hatch.color'] = hatch_1_color
plt.rcParams['hatch.linewidth'] = 0.3


amf_loc = 1
smf_loc = 2
ax_1.barh(amf_loc, Td_1, left = T1, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T1 + Td_1/2, amf_loc - bar_width/2, marker=marker_list[0], color=marker_color)
ax_1.barh(smf_loc, Td_2, left = T2, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T2 + Td_2/2, smf_loc - bar_width/2, marker=marker_list[1], color=marker_color)
ax_1.barh(smf_loc, Td_3, left = T3, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T3 + Td_3/2, smf_loc - bar_width/2, marker=marker_list[2], color=marker_color)


# 5g aka
# ax.barh(1, Td_4, left = T4, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(1, Td_5, left = T5, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(3, Td_6, left = T6, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(3, Td_7, left = T7, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(4, Td_8, left = T8, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(4, Td_9, left = T9, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(4, Td_10, left = T10, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(4, Td_11, left = T11, height=bar_width, color='none', hatch='..', zorder = 0)

amf_loc = 1
ausf_loc = 3
udm_loc = 4
ax_1.barh(amf_loc, Td_4, left = T4, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T4 + Td_4/2, amf_loc - bar_width/2, marker=marker_list[3], color=marker_color)
ax_1.barh(amf_loc, Td_5, left = T5, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T5 + Td_5/2, amf_loc - bar_width/2, marker=marker_list[4], color=marker_color)
ax_1.barh(ausf_loc, Td_6, left = T6, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T6 + Td_6/2, ausf_loc - bar_width/2, marker=marker_list[5], color=marker_color)
ax_1.barh(ausf_loc, Td_7, left = T7, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T7 + Td_7/2, ausf_loc - bar_width/2, marker=marker_list[6], color=marker_color)
ax_1.barh(udm_loc, Td_8, left = T8, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T8 + Td_8/2, udm_loc - bar_width/2, marker=marker_list[7], color=marker_color)
ax_1.barh(udm_loc, Td_9, left = T9, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T9 + Td_9/2, udm_loc - bar_width/2, marker=marker_list[8], color=marker_color)
ax_1.barh(udm_loc, Td_10, left = T10, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T10 + Td_10/2, udm_loc - bar_width/2, marker=marker_list[9], color=marker_color)
ax_1.barh(udm_loc, Td_11, left = T11, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T11 + Td_11/2, udm_loc - bar_width/2, marker=marker_list[10], color=marker_color)

# session setup
# ax.barh(1, Td_12, left = T12, height=bar_width, color='none', hatch='xx', zorder = 0)
# ax.barh(2, Td_13, left = T13, height=bar_width, color='none', hatch='xx', zorder = 0)
# ax.barh(1, Td_14, left = T14, height=bar_width, color='none', hatch='xx', zorder = 0)

amf_loc = 1
smf_loc = 2
ax_1.barh(amf_loc, Td_12, left = T12, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T12 + Td_12/2, amf_loc - bar_width/2, marker=marker_list[11], color=marker_color)
ax_1.barh(smf_loc, Td_13, left = T13, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T13 + Td_13/2, smf_loc - bar_width/2, marker=marker_list[12], color=marker_color)
ax_1.barh(amf_loc, Td_14, left = T14, height=-1*bar_width, color=bar_1_color, alpha=opacity, ec=bar_1_edgecolor, lw=line_width, zorder = 1, align='edge') 
ax_1.plot(T14 + Td_14/2, amf_loc - bar_width/2, marker=marker_list[13], color=marker_color)


#---------------------------------------------------------------------------------------------

folder = folder_nowave
csvpath = folder + "/table.csv"
df = pd.read_csv(csvpath, header=0, index_col=[0])
# print(df)

client_vnfs = ['AMF', 'SMF', 'AUSF', 'UDM']

# registration times
row_1 = df.loc[(df['from'] == "amf") & (df['to'] == "nrf")]
T1 = 0
Td_1 = row_1.iloc[0]['time']
ax_1_ticks.append(Td_1)

row_2_3 = df.loc[(df['from'] == "smf") & (df['to'] == "nrf")]
T2 = T1 + 200
Td_2 = row_2_3.iloc[0]['time']
T3 = T2 + Td_2
ax_1_ticks.append(T3)
Td_3 = row_2_3.iloc[1]['time']
ax_1_ticks.append(T3+Td_3)

# 5g aka
row_4_5 = df.loc[(df['from'] == "amf") & (df['to'] == "ausf")]
# T4 = 2000
# T4 = T3 + Td_3 + 200
T4 = Tstart2
Td_4 = row_4_5.iloc[0]['time']
T5 = T4 + Td_4 + 0.5
Td_5 = row_4_5.iloc[1]['time']

row_6_7 = df.loc[(df['from'] == "ausf") & (df['to'] == "udm")]
Td_6 = row_6_7.iloc[0]['time']
# T6 = T4 - 30 + Td_4 - Td_6   # avg OAI time
T6 = T4 + 10 # propagation delay
Td_7 = row_6_7.iloc[1]['time']
T7 = T5 + 10 # propagation delay   # avg OAI time

row_8_9_10_11 = df.loc[(df['from'] == "udm") & (df['to'] == "udr")]
T8 = T6 + 10   # propagation delay 
Td_8 = row_8_9_10_11.iloc[0]['time']
T9 = T8 + Td_8  
Td_9 = row_8_9_10_11.iloc[1]['time']
T10 = T7 + 10  # propagation delay
Td_10 = row_8_9_10_11.iloc[2]['time']
T11 = T10 + Td_10
Td_11 = row_8_9_10_11.iloc[3]['time']


# session setup
row_12_14 = df.loc[(df['from'] == "amf") & (df['to'] == "smf")]
# T12 = T5 + Td_5 + 500
# T12 = T11 + Td_11 + 200 
T12 = Tstart3
Td_12 = row_12_14.iloc[0]['time']
row_13 = df.loc[(df['from'] == "smf") & (df['to'] == "amf")]
T13 = T12 + Td_12
Td_13 = row_13.iloc[0]['time']
T14 = T13 + Td_13
Td_14 = row_12_14.iloc[1]['time']


# fig, ax = plt.subplots()
bar_width=0.4
bar_2_color=xkcd_colors['xkcd:golden rod']
bar_2_edgecolor=xkcd_colors['xkcd:almost black']
hatch_2_color=xkcd_colors['xkcd:browny orange']
# opacity=0.5
opacity=1
line_width=1
# hatch_width=0.5

plt.rcParams['hatch.color'] = hatch_2_color
plt.rcParams['hatch.linewidth'] = 0.3
# vnf registration
# ax.barh(1 + bar_width, Td_1, left = T1, height=bar_width, color='none', hatch='\\\\', zorder = 0)
# ax.barh(2 + bar_width, Td_2, left = T2, height=bar_width, color='none', hatch='\\\\', zorder = 0)
# ax.barh(2 + bar_width, Td_3, left = T3, height=bar_width, color='none', hatch='\\\\', zorder = 0)

amf_loc = 1
smf_loc = 2
ax_1.barh(amf_loc, Td_1, left = T1, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T1 + Td_1/2, amf_loc+bar_width/2, marker=marker_list[0], color=marker_color)
ax_1.barh(smf_loc, Td_2, left = T2, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T2 + Td_2/2, smf_loc+bar_width/2, marker=marker_list[1], color=marker_color)
ax_1.barh(smf_loc, Td_3, left = T3, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T3 + Td_3/2, smf_loc+bar_width/2, marker=marker_list[2], color=marker_color)

# ax.text(client_vnfs[0] + bar_width, T1+Td_1/2, 'PUT')

# 5g aka
# ax.barh(1 + bar_width, Td_4, left = T4, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(1 + bar_width, Td_5, left = T5, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(3 + bar_width, Td_6, left = T6, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(3 + bar_width, Td_7, left = T7, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(4 + bar_width, Td_8, left = T8, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(4 + bar_width, Td_9, left = T9, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(4 + bar_width, Td_10, left = T10, height=bar_width, color='none', hatch='..', zorder = 0)
# ax.barh(4 + bar_width, Td_11, left = T11, height=bar_width, color='none', hatch='..', zorder = 0)

amf_loc = 1
ausf_loc = 3
udm_loc = 4
ax_1.barh(amf_loc, Td_4, left = T4, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T4 + Td_4/2, amf_loc + bar_width/2, marker=marker_list[3], color=marker_color)
ax_1.barh(amf_loc, Td_5, left = T5, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T5 + Td_5/2, amf_loc + bar_width/2, marker=marker_list[4], color=marker_color)
ax_1.barh(ausf_loc, Td_6, left = T6, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T6 + Td_6/2, ausf_loc + bar_width/2, marker=marker_list[5], color=marker_color)
ax_1.barh(ausf_loc, Td_7, left = T7, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T7 + Td_7/2, ausf_loc + bar_width/2, marker=marker_list[6], color=marker_color)
ax_1.barh(udm_loc, Td_8, left = T8, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T8 + Td_8/2, udm_loc + bar_width/2, marker=marker_list[7], color=marker_color)
ax_1.barh(udm_loc, Td_9, left = T9, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T9 + Td_9/2, udm_loc + bar_width/2, marker=marker_list[8], color=marker_color)
ax_1.barh(udm_loc, Td_10, left = T10, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T10 + Td_10/2, udm_loc + bar_width/2, marker=marker_list[9], color=marker_color)
ax_1.barh(udm_loc, Td_11, left = T11, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T11 + Td_11/2, udm_loc + bar_width/2, marker=marker_list[10], color=marker_color)

# session setup
# ax.barh(1 + bar_width, Td_12, left = T12, height=bar_width, color='none', hatch='xx', zorder = 0)
# ax.barh(2 + bar_width, Td_13, left = T13, height=bar_width, color='none', hatch='xx', zorder = 0)
# ax.barh(1 + bar_width, Td_14, left = T14, height=bar_width, color='none', hatch='xx', zorder = 0)

amf_loc = 1
smf_loc = 2
ax_1.barh(amf_loc, Td_12, left = T12, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T12 + Td_12/2, amf_loc + bar_width/2, marker=marker_list[11], color=marker_color)
ax_1.barh(smf_loc, Td_13, left = T13, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T13 + Td_13/2, smf_loc + bar_width/2, marker=marker_list[12], color=marker_color)
ax_1.barh(amf_loc, Td_14, left = T14, height=bar_width, color=bar_2_color, alpha=opacity, ec=bar_2_edgecolor, lw=line_width, zorder = 1, align='edge')
ax_1.plot(T14 + Td_14/2, amf_loc + bar_width/2, marker=marker_list[13], color=marker_color)

labels = ['with WAVE', 'without WAVE']
h1 = mpatches.Patch(color=bar_1_color, ec=bar_1_edgecolor, label=labels[0])
h2 = mpatches.Patch(color=bar_2_color, ec=bar_2_edgecolor, label=labels[1])
handles1 = [h1, h2]

h_0 = mlines.Line2D([], [], linestyle='None', label=r'$Client\longrightarrow Host\ (Request)$') 
h_1 = mlines.Line2D([], [], color=marker_color, marker=marker_list[0], linestyle='None', label=r'AMF$\longrightarrow$ NRF (PUT)') 
h_2 = mlines.Line2D([], [], color=marker_color, marker=marker_list[1], linestyle='None', label=r'SMF$\longrightarrow$ NRF (POST)') 
h_3 = mlines.Line2D([], [], color=marker_color, marker=marker_list[2], linestyle='None', label=r'SMF$\longrightarrow$ NRF (PUT)') 

h_4 = mlines.Line2D([], [], color=marker_color, marker=marker_list[3], linestyle='None', label=r'AMF$\longrightarrow$ AUSF (POST)') 
h_5 = mlines.Line2D([], [], color=marker_color, marker=marker_list[5], linestyle='None', label=r'AUSF$\longrightarrow$ UDM (POST)') 
h_6 = mlines.Line2D([], [], color=marker_color, marker=marker_list[7], linestyle='None', label=r'UDM$\longrightarrow$ UDR (GET)') 
h_7 = mlines.Line2D([], [], color=marker_color, marker=marker_list[8], linestyle='None', label=r'UDM$\longrightarrow$ UDR (PATCH)') 
h_8 = mlines.Line2D([], [], color=marker_color, marker=marker_list[4], linestyle='None', label=r'AMF$\longrightarrow$ AUSF (POST)') 
h_9 = mlines.Line2D([], [], color=marker_color, marker=marker_list[6], linestyle='None', label=r'AUSF$\longrightarrow$ UDM (POST)') 
h_10 = mlines.Line2D([], [], color=marker_color, marker=marker_list[9], linestyle='None', label=r'UDM$\longrightarrow$ UDR (GET)') 
h_11 = mlines.Line2D([], [], color=marker_color, marker=marker_list[10], linestyle='None', label=r'UDM$\longrightarrow$ UDR (PUT)') 

h_12 = mlines.Line2D([], [], color=marker_color, marker=marker_list[11], linestyle='None', label=r'AMF$\longrightarrow$ SMF (POST)') 
h_13 = mlines.Line2D([], [], color=marker_color, marker=marker_list[12], linestyle='None', label=r'SMF$\longrightarrow$ AMF (POST)') 
h_14 = mlines.Line2D([], [], color=marker_color, marker=marker_list[13], linestyle='None', label=r'AMF$\longrightarrow$ SMF (POST)') 

# Set the x-axis labels and title
ylist = np.arange(1, len(client_vnfs)+1)
y_axis_label = 'Client VNF'
x_axis_label = 'Latency (ms)'
plot_title = "Request completion time in 5G core framework"
plot_1_subtitle = "VNF registration"
plot_2_subtitle = "5G AKA"
plot_3_subtitle = "Session setup"

ax_1_ticks.sort()
ax_1.set_yticks(np.arange(1, 5))
ax_1.set_yticklabels(client_vnfs[0:4])
ax_1.set_xticks(ax_1_ticks)
ax_1.set_xticklabels(['t0 (0)', ax_1_ticks[1], ax_1_ticks[2], 't1 (0)',  ax_1_ticks[4] - 400, ax_1_ticks[5] - 400, ax_1_ticks[6] - 400 , ax_1_ticks[7] - 400], rotation=90)
ax_1.set_ylabel(y_axis_label)
ax_1.set_xlabel(x_axis_label)
legend1 = ax_1.legend(handles=handles1, loc="upper left")
handles2 = [h_0, h_1, h_2, h_3, h_4, h_5, h_6, h_7, h_8, h_9, h_10, h_11, h_12, h_13, h_14]
legend2 = fig_1.legend(handles=handles2, loc="outside upper right")
ax_1.add_artist(legend1)
ax_1.add_artist(legend2)
# fig_1.suptitle(plot_title)
# ax_1.set_title(plot_1_subtitle)
fig_1.savefig("fig1-latency.svg", format='svg', bbox_inches="tight")
fig_1.savefig("fig1-latency.pdf", format='pdf', bbox_inches="tight")

ax_2.set_yticks(np.arange(1,4))
ax_2.set_yticklabels([client_vnfs[0], client_vnfs[2], client_vnfs[3]])
ax_2.set_ylabel(y_axis_label)
ax_2.set_xlabel(x_axis_label)
legend1 = ax_2.legend(handles=handles1, bbox_to_anchor=(1.04, 1), loc="upper left")
handles2 = [h_0, h_4, h_5, h_6, h_7, h_8, h_9, h_10, h_11]
legend2 = ax_2.legend(handles=handles2, bbox_to_anchor=(1.04, 0.5), loc="center left")
ax_2.add_artist(legend1)
ax_2.add_artist(legend2)
fig_2.suptitle(plot_title)
ax_2.set_title(plot_2_subtitle)
fig_2.savefig("fig2-latency.svg", format='svg', bbox_inches="tight")
fig_2.savefig("fig2-latency.pdf", format='pdf', bbox_inches="tight")

ax_3.set_yticks(np.arange(1,3))
ax_3.set_yticklabels(client_vnfs[0:2])
ax_3.set_ylabel(y_axis_label)
ax_3.set_xlabel(x_axis_label)
legend1 = ax_3.legend(handles=handles1, bbox_to_anchor=(1.04, 1), loc="upper left")
handles2 = [h_0, h_12, h_13, h_14]
legend2 = ax_3.legend(handles=handles2, bbox_to_anchor=(1.04, 0.5), loc="center left")
ax_3.add_artist(legend1)
ax_3.add_artist(legend2)
fig_3.suptitle(plot_title)
ax_3.set_title(plot_3_subtitle)
fig_3.savefig("fig3-latency.svg", format='svg', bbox_inches="tight")
fig_3.savefig("fig3-latency.pdf", format='pdf', bbox_inches="tight")
# ----------------------------------------------------------------------------------------------------------------

# plt.switch_backend('TkAgg')
# plt.show()
