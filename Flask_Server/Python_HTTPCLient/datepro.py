import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import datetime

# create data
y = [ 2,4,6,8,10,12,14,16,18,20 ]
x = [datetime.datetime.now() + datetime.timedelta(hours=i) for i in range(len(y))]

# plot
plt.plot(x,y)
plt.gcf().autofmt_xdate()
plt.show()