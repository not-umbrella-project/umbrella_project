#https://raw.githubusercontent.com/not-umbrella-project/umbrella_project/master/Server/test-socket-server.py
def ifStringLenGreaterThan3(a):
    if len(a)>3:
        return "true"
    else:
        return "false"

import socket
HOST = ''
PORT = 22222
while 1:
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()

    print('Connected by', addr)
    while (conn.fileno() !=-1):
        data = conn.recv(4096)
        if not data:
            print("not data")
        else:
            d= data.decode()
            print(d)
            conn.sendall(ifStringLenGreaterThan3(d).encode())




