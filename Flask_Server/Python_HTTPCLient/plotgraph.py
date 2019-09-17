import http.client
from matplotlib import pyplot as plt
conn = http.client.HTTPConnection("192.168.0.120", 5000)
conn.request("GET", "/")
r1 = conn.getresponse()
print(r1.read())
conn.close()
