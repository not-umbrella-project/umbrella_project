#get data and control clients
#python3


#imports
try:
        import logging
        logging.basicConfig(filename="server_main_DOT_py.log", filemode="a", format="%(asctime)s %(name)s:%(levelname)s:%(message)s", datefmt="%Y-%M-%d %H:%M:%S", level=logging.DEBUG)
except:
        print("exception: cannot import logging")
try:
	import os
	import os.path
except:
	print("exception: cannot import os")
try:
	import subprocess
except:
	print("exception: cannot import subprocess")
try:
	from datetime import datetime
	import time
except:
	print("exception: cannot import datetime")
try:
	import socket
except:
	print("exception: cannot import socket")
logging.info("started")
#https://stackoverflow.com/questions/3730964/python-script-execute-commands-in-terminal

#body
"""
def print_to_file(message):
        #

def log_line(mystr)
"""


#send data
def p(HOST, PORT, message, client):

    #source: https://realpython.com/python-sockets/
    #status: WORKING
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


def datawrite(filename, mystring):
        fname = filename+".txt"
        f = open(fname, "r+")
        f.write(mystring)
        f.close()

def dataappend(filename, mystring):
        fname = filename+".txt"
        f = open(fname, "a")
        f.write("\n"+mystring)
        f.close()

def datanewfile(filename):
        fname = filename+".txt"
        f = open(fname, "x")
        f.close()

def dataadduser(name):
        #make sure no same name
        try:
                datanewfile(name)
                datawrite(name, "r")
                dataappend("1server_data_userList", name)
        except:
                logging.critical("trying to create new file with existing name")

def isNewUser(name):
        f = open("1server_data_userList.txt")
        while True:
                l = f.readline().strip("\n")
                print(l)
                if l:
                        if l==(name):
                                f.close()
                                return True
                else:
                       break
        f.close()
        return False

def datauserreturn(name):
        line = "r@ "+time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
        dataappend(name, line)
        datawrite(name, "r")

def dataReturned(name):
        fname = name+".txt"
        file = open(fname, "r")
        h=file.readline(1)
        if h=="r":
                return True
        elif h=="b":
                return False
        logging.critical("data file header isn't r or b")


def handleBorrow(name):
        if isNewUser(name):
                dataadduser(name)
        if dataReturned(name):
                #def datauserborrow(name)
                line = "b@ "+time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
                dataappend(name, line)
                datawrite(name, "b")
                ###OPEN
        else:
                return "don't open"
#integrity check

#testing
print(isNewUser("ddda"))
dataadduser("ddda")

if dataReturned("MEE"):
        print(1111111)

file = open("MEE.txt", "r")
print("\n"+file.read())

print(isNewUser("ddda"))


#main loop
cycle_count = 0
cycle_count_multiplier = 10
i=1
logging.info("main loop also started")
"""
while True:
        UPDATE BOX STATUS
                USER REQUEST: B, R, NEWUSER
                PROBLEMS --> ALARM ME


        
        if(i>cycle_count_multiplier):
        	cycle_count +=1
        	i=1

#error message
logging.critical("main loop terminated, with " + str(cycle_count*cycle_count_multiplier) + " successful cycles")
"""
