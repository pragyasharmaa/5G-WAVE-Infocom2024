#!/bin/python3

import glob
import pandas as pd
import numpy as np
from collections import defaultdict
# from dateutil import parser
import datetime
import sys

folder = sys.argv[1]

table_1_csv = folder + "/table.csv"
table_2_csv = folder + "/table-verify.csv"

df_1 = pd.read_csv(table_1_csv, header=0, index_col=[0])
df_2 = pd.read_csv(table_2_csv, header=0, index_col=[0])

verify = df_2['verify']
df = df_1.join(verify)

csv_file = folder + "/" + "finaltable.csv"  
df.to_csv(csv_file)            
