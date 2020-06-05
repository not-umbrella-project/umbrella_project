#get data and control clients
#python3


#imports
try:
    import logging
    logging.basicConfig(filename="server_main_DOT_py.log", filemode="a", format="%(asctime)s %(name)s:%(levelname)s:%(message)s", datefmt="%Y-%M-%d %H:%M:%S", level=logging.INFO)
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
                """


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
        if l:
            if l==(name):
                f.close()
                return False
        else:
            break
    f.close()
    return True

def datauserreturn(name):
    line = "r@ "+time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    dataappend(name, line)
    datawrite(name, "r")

def datauserborrow(name):
    line = "b@ "+time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    dataappend(name, line)
    datawrite(name, "b")

def dataReturned(name):
    fname = name+".txt"
    file = open(fname, "r")
    h=file.readline(1)
    if h=="r":
        return 1 #returned
    elif h=="b":
        return 0 #havent return
    logging.critical("data file header isn't r or b")

def handleBorrow(name):
    if isNewUser(name):
        dataadduser(name)
    if dataReturned(name)==1:
        datauserborrow(name)
        return 1#"open, can borrow"
    elif dataReturned(name) == 0:
        return 2#"don't open, because you haven't return yet "
    else:
        return 3#"sorry there is a error"

def handleReturn(name):
    if isNewUser(name):
        return 2 #"don't open, because you borrow anything yet"
    if dataReturned(name)==1:
        return 2 #"don't open, because you borrow anything yet"
    elif dataReturned(name) == 0:
        return 1 #"open, pls"
    else:
        return 3#"sorry there is a error"

#def handleReturn(name):
#integrity check

#testing
"""
datauserreturn("ddda")
handleBorrow("ddda")
file = open("ddda.txt", "r")
print("\n"+file.read())
"""

#main loop
cycle_count = 0
cycle_count_multiplier = 10
i=1
logging.info("main loop also started")

HOST = ''
PORT = 33080
no_data = 0
while 1:
    #socket
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()

    #logging.info
    print('debug: Connected by', addr)
    
    while (conn.fileno() !=-1):
        print('debug: 2nd while')
        try:
            data = conn.recv(4096)
            print("data recieved:",data)
            if not data:
                not_data+=1
                if not_data> 10:
                    not_data=0
                    print("not data")
            else:
                d= data.decode()
            if d[0]==str(0):#borrow
                sent = handleBorrow(d.strip(d[0]))
            elif d[0]==str(1): #return
                sent = handleReturn(d.strip(d[0]))
            conn.sendall(str(sent).encode())
            print("sent data" + str(sent))
        except:
            print("Disconnected by",addr)
            break

#error message
logging.critical("main loop terminated, with " + str(cycle_count*cycle_count_multiplier) + " successful cycles")
"""
        UPDATE BOX STATUS
                USER REQUEST: B, R, NEWUSER
                PROBLEMS --> ALARM ME

        if(i>cycle_count_multiplier):
        	cycle_count +=1
        	i=1
"""
