import socket

HOST = ''
PORT = 22222
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    #https://docs.bitnami.com/virtual-machine/faq/administration/use-firewall/
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            conn.sendall(data)
            print(data)
