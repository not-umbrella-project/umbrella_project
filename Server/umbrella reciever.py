import socket

HOST = '34.80.90.238'
PORT = 22222

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.sendall(b'f')
data = s.recv(1024)

print('Received', repr(data))
print(data)
s.sendall(b'f')


