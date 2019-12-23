
#send egress_message to server at (server_address, server_port), and return received message
def talk_to_server(server_address, server_port, egress_message):
    #imports
    try:
        import socket
    except:
        print("ERR cannot import: ", "socket")

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server_address, server_port))
    s.sendall(egress_message.encode())
    data = s.recv(4096)
    ingress_message = data.decode()
    return ingress_message

port = '34.80.90.238' #'192.168.1.15'
print(talk_to_server(port, 22222,"aaa"))

