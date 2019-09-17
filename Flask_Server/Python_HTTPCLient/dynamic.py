import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
from datetime import datetime

fig = plt.figure()
ax1 = fig.add_subplot(2,1,1)
ax2 = fig.add_subplot(2,1,2)

now = datetime.now()

def animate(i):
    pullData = open("sampleText.txt","r").read()
    dataArray = pullData.split('\n')
    xar = []
    xvar = []
    yar = []
    yvar = []
    for eachLine in dataArray:
        if len(eachLine)>1:
            x,y = eachLine.split(',')
            xar.append(x) #now.strftime("%H:%M:%S")
            xvar.append(x)
            yar.append(int(y))
            yvar.append(int(y)*2)
#            time.sleep(10)
    ax1.clear()
    ax2.clear()
#    ax1.plot(xar,yar)
#    ax2.plot(xvar,yvar)
    ax1.bar(xar,yar)
    labels = ax1.get_xticklabels()
    plt.setp(labels, rotation=45, horizontalalignment='right')
    ax2.bar(xvar,yvar, color='red')
ani = animation.FuncAnimation(fig, animate, interval=1000)
plt.show()
