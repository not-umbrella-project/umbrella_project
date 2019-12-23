# -*- coding: utf-8 -*-
"""
Created on Mon Nov 25 22:26:43 2019

@author: cj020
"""

import socket
s = socket.socket()
s.bind(('0.0.0.0', 8090))
s.listen(0)
print("program starts")
while True:
    client, addr = s.accept()
    while True:
        content = client.recv(32)
        if len(content) ==0:
           break
        else:
            print(content)
    print("Closing connection")
    client.close()