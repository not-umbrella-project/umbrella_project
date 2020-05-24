import time
#send egress_message to server at (server_address, server_port), and return received message
"""
def talk_to_server(server_address, server_port, egress_message):
    #imports
    try:
        import socket
    except:
        print("ERR cannot import: ", "socket")

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server_address, server_port))

    #s.sendall(egress_message.encode())
    print("NEW socket")

    i=1
    while 1:#i<10:
        print("here")
        s.sendall(str(i).encode())
        data = s.recv(4096)
        ingress_message = data.decode()
        #return ingress_message
        print(ingress_message, type(ingress_message))
        time.sleep(0.1)
        print(i)
        i+=1
    print("breaked")
    s.close()
"""
def talk_to_server(server_address, server_port, egress_message):
    #imports
    try:
        import socket
    except:
        print("ERR cannot import: ", "socket")

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server_address, server_port))
    print("NEW socket created")
    s.sendall(egress_message.encode())
    print("sent "+egress_message+" to "+ server_address)
    data = s.recv(4096)
    ingress_message = data.decode()
    #return ingress_message
    return (ingress_message, type(ingress_message))
    print("disconnect")
    s.close()


print(talk_to_server('192.168.1.13', 33080,"aa"))
"""
print(talk_to_server('34.80.90.238', 33080,"aa\n"))
print("also breaked")

print(talk_to_server('34.80.90.238', 33080,"aa\n"))
print("sregr")
print(talk_to_server('34.80.90.238', 33080,"aa\n"))


"""
