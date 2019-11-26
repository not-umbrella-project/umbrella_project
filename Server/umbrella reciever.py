import socket

HOST = '192.168.1.8'
PORT = 22345

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print(1)
s.connect((HOST, PORT))
print(2)
s.sendall('faaaaaaafrom my laptop vrerhjkbaef')
data = s.recv(1024)

print('Received', repr(data))

while 1:
    a = raw_input("send here: " )
    a = str("'"+a+"'")
    print(a)
    s.sendall(a)
