#get data and control clients
#python3


#imports
try:
	import os
except:
	print("exception: cannot import os")
try:
	import subprocess
except:
	print("exception: cannot import subprocess")
try:
	from datetime import datetime
except:
	print("exception: cannot import datetime")
try:
	import socket
except:
	print("exception: cannot import socket")
#https://stackoverflow.com/questions/3730964/python-script-execute-commands-in-terminal


#body
"""
def print_to_file(message):
        #

def log_line(mystr)
"""


#send data
def push_data(HOST, PORT, message, client):

    #source: https://realpython.com/python-sockets/
    #status: WORKING
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
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


#read [client]_data.py to get data ///to be changed
def get_data(client):
        #
        b = null



#main loop
cycle_count = 0
while True:
	cycle_count +=1
	push_data('', 12345, "aa",1)



#error message
error_message = "main loop terminated, with " + str(cycle_count) + " successful cycles"
printfile(error_message)
