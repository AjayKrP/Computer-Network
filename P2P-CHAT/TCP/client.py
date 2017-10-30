import socket
import time

HOST = "127.0.0.1"
PORT = 5000
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))
while True:
      data = input("<client>: ")
      s.send(str.encode(data))
      msg = s.recv(1024)
      print ("<server> : " +str(msg, 'utf-8'))
      if data=="bye" or msg=="bye":
           print ("Exiting...........")
           time.sleep(1)
           break