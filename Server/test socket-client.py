import socket

HOST = '192.168.1.15'
PORT = 22222
message = "aaa"
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.sendall(message.encode())
data = s.recv(4096)

print('Received', repr(data))

