import http.client
import random
import time

times = 20

for i in range(times) :
    
    conn1 = http.client.HTTPConnection("192.168.1.100", 5006)
    x = str(random.randint(1, 11))
    conn1.request("GET", "/sensor1/"+x)
    print(x)
    conn1.close()
    
    conn2 = http.client.HTTPConnection("192.168.1.100", 5006)
    x = str(random.randint(1, 11))
    conn2.request("GET", "/sensor2/"+x)
    print(x)
    conn2.close()
    
    time.sleep(4)
    
    
