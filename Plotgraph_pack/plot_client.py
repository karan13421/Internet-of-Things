import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import http.client
import numpy as np
import time
from datetime import datetime

current_time = ["3:35:40","4:06:05", "5:07:12", "6:05:14"]
sensor1= [3, 5, 6, 2]
sensor2 = [2, 4, 7, 6]

#plt.ion()
#fig = plt.figure()
#ax = fig.add_subplot()
fig, ax = plt.subplots()

while 1 :
    current_time.pop()
    sensor1.pop()
    sensor2.pop()


    conn1 = http.client.HTTPConnection("192.168.1.100", 5006)
    conn1.request("GET", "/data/sensor1")
    r1 = conn1.getresponse()
    r1 = int(r1.read())
    print(r1)
    sensor1.insert(0,r1)
    conn1.close()
    
    conn2 = http.client.HTTPConnection("192.168.1.100", 5006)
    conn2.request("GET", "/data/sensor2")
    r2 = conn2.getresponse()
    r2 = int(r2.read())
    print(r2)
    sensor2.insert(0,r2)
    conn2.close()
    
    now = datetime.now()
    current_time.insert(0,now.strftime("%H:%M:%S"))
    print(current_time)
    print("\n")
    
##############################################################################
    ax.clear()
    
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
    plt.legend()
    plt.draw()
    plt.pause(0.01)
    time.sleep(6)

#ani = animation.FuncAnimation(fig, animateer(), interval=1000)
plt.show()
