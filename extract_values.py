#!/usr/bin/env python3

import sys
import re
import matplotlib.pyplot as plt
import statistics as st
import numpy as np

# Read the command line for getting the log file from minicon as input
argLen = len(sys.argv)

if (argLen != 2):
    print("Error in the input! \nUsage: " + sys.argv[0] + " <log-file-name>")
    sys.exit()

# Read the log file and store in a string array
with open(sys.argv[1], 'r') as file:
    data = file.readlines()

# May have to change this based on how the log file is written to.
REGEX_STRING = "val=([-]*[0-9]+)"
stringPattern = re.compile(REGEX_STRING)

# Store necessary data in lists
vals = []
meds = []

# Add extracted data to the error list
for s in data:
    matchObj = stringPattern.match(s) 
    if matchObj:
        vals.append(int(matchObj.group(1)))

# Removing outliers from the extracted data
MEDIAN_WINDOW_SIZE = 20

# Store median values as per the size of the median window
medIndex = 0 
while medIndex < len(vals):
    if (medIndex + MEDIAN_WINDOW_SIZE) < len(vals):
        med = st.median(vals[medIndex:medIndex + MEDIAN_WINDOW_SIZE])
        meds.append(med)
        medIndex += MEDIAN_WINDOW_SIZE
    else:
        med = st.median(vals[medIndex:-1])
        meds.append(med)
        break

meds = np.array(meds)
meds = meds/10
meds = np.array(meds, dtype ='int')

# Currently against indices, can be changed to the actual timestamp values with some regex modifs
indicesMeds = list(range(0, len(meds)))

# Plot using matplotlib

plt.figure()
tickPlot = plt.gca()
tickPlot.set_title("Intensity values")
tickPlot.set_ylabel("Intensity (voltage)")
tickPlot.set_xlabel("iteration")
tickPlot.plot(indicesMeds, meds, 'o')

plt.show()