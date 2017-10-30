import socket
import time
from _thread import *
HOST = ""
PORT = 5000
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.bind((HOST, PORT))
except socket.error as e:
    print(str(e))
s.listen(10)

def threaded_client(conn):
    while True:
        data = conn.recv(2048)
        reply = str(data, 'utf-8')
        print('<client>:'+reply)
        if not data:
            break
        msg = input('<server>: ')
        conn.send(str.encode(msg))
    conn.close()
while True:
    conn, addr = s.accept()
    print('connected to: '+addr[0] +':'+str(addr[1]))
    start_new_thread(threaded_client, (conn,))

