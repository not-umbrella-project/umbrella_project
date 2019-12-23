
import socket
print("debug")
HOST = ''
PORT = 22222
sends = b's'
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen()
conn, addr = s.accept()

print('Connected by', addr)

data = conn.recv(4096)
d= data.decode()
print(type(d))
if not data:
    print("not data")

conn.sendall(sends)
