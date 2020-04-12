#imports
try:
    import socket
except:
    print("ERR cannot import: ", "socket")


server_address ='34.80.90.238'
server_port=33080
message= "aoligei!"

#creat new socket
print("debug: creating NEW socket ")
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((server_address, server_port))

#send message
print("debug: sending'" + message)
s.sendall(str(message).encode())

#receive message
data = s.recv(4096)
ingress_message = data.decode()
print(ingress_message)

print("debug: closing socket")
s.close()








