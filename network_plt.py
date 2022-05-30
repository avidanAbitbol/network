import numpy as np


'plot bar plot comparing Reno and Cubic'
import matplotlib.pyplot as plt
# set width of bar
barWidth = 0.25
fig = plt.subplots(figsize=(12, 8))
# set height of bar
list_avg_reno = [0.1175, 0.333451, 0.261088, 1.612884, 8.736944]
list_avg_cubic = [0.154266, 0.229504, 0.493127, 1.752287,0]
list_total_reno = [0.587502, 1.667255, 1.305438, 8.864418, 43.684721]
list_total_cubic = [0.771332, 1.147518, 2.465635, 8.761433, 0]

# Set position of bar on X axis
br1 = np.arange(len(list_total_cubic))
br2 = [x + barWidth for x in br1]
br3 = [x + barWidth for x in br2]

# Make the plot
plt.bar(br1, list_total_reno, color='black', width=barWidth,
        edgecolor='grey', label='reno')
plt.bar(br2, list_total_cubic, color='red', width=barWidth,
        edgecolor='grey', label='cubic')


# Adding Xticks
plt.xlabel('lost precnt', fontweight='bold', fontsize=15)
plt.ylabel('total time', fontweight='bold', fontsize=15)
plt.xticks([r + barWidth for r in range(len(list_total_cubic))],
           ['10%', '15%', '20%', '25%', '30%'])

plt.legend()
plt.show()
# Set position of bar on X axis
br1 = np.arange(len(list_avg_cubic))
br2 = [x + barWidth for x in br1]
br3 = [x + barWidth for x in br2]

# Make the plot
plt.bar(br1, list_avg_reno, color='g', width=barWidth,
        edgecolor='grey', label='reno')
plt.bar(br2, list_avg_cubic, color='b', width=barWidth,
        edgecolor='grey', label='cubic')


# Adding Xticks
plt.xlabel('lost precnt', fontweight='bold', fontsize=15)
plt.ylabel('average time', fontweight='bold', fontsize=15)
plt.xticks([r + barWidth for r in range(len(list_avg_cubic))],
           ['10%', '15%', '20%', '25%', '30%'])

plt.legend()
plt.show()