# -*- coding: utf-8 -*-
"""
Created on Mon Dec 23 21:22:18 2019

@author: cj020
"""

import socket

HOST = '34.80.90.238'
PORT = 22222
message = "aaaaaaaaa"
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.sendall(message.encode())
data = s.recv(4096)

print('Received', repr(data))