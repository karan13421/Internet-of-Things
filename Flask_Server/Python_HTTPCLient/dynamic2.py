import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import time
from datetime import datetime

now = datetime.now()
fig, ax = plt.subplots()

def animate(i):
    pullData = open("sampleText.txt","r").read()
    dataArray = pullData.split('\n')
    current_time = []
    sensor1= []
    sensor2 = []
    for eachLine in dataArray:
        if len(eachLine)>1:
            x,y = eachLine.split(',')
            current_time.append(x)
            sensor1.append(int(y))
            sensor2.append(int(y)*2)
    ax.clear()
##############################################################################

    loc = np.arange(len(current_time))
    width =0.35
    ax.bar(loc - width/2, sensor1, width, label="sensor1", color='red')
    ax.bar(loc + width/2, sensor2, width, label="sensor2", color='blue')
#############################################################################
    ax.set_ylabel('Range')
    ax.set_title('Sensor data compairision')
    ax.set_xticks(loc)
    ax.set_xticklabels(current_time)
    labels = ax.get_xticklabels()
    plt.setp(labels, rotation=45, horizontalalignment='right')
   
ani = animation.FuncAnimation(fig, animate, interval=1000)
plt.show()
