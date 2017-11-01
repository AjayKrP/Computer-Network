import socket, pickle, random, argparse, threading
import readline
from packet import Packet
import sys
'''
WARNING : input/output is kind of wonky use ncurses for better experience 
'''
CURSOR_UP_ONE = '\x1b[1A'
ERASE_LINE = '\x1b[2M'
RECV_SIZE = 1024*10
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
local_port = random.randint(1000, 2 ** 16)
sock.bind(('', local_port))
lock = threading.Lock()
client_id = random.randint(0,99999)


def message_listener():
    while True:
        data, addr = sock.recvfrom(RECV_SIZE)
        recv_packet = pickle.loads(data)
        if recv_packet.ptype == 'M':
            print(CURSOR_UP_ONE + ERASE_LINE)
            print(recv_packet.data)
            readline.redisplay()



def main(raddr):

    threading.Thread(target=message_listener).start()
    packet = Packet(ptype='H')
    server = ('127.0.0.1',8089)
    sock.sendto(pickle.dumps(packet), server)

    while True:
        message = input()
        packet = Packet(ptype='M', data='<{}> {}\n'.format(client_id, message))
        sock.sendto(pickle.dumps(packet), server)



if __name__ == '__main__':
   # parser = argparse.ArgumentParser(description='Multi user chat with UDP')
   # parser.add_argument('--port', type=int, required=True, help='Port to connect to')
   # parser.add_argument('--host', type=str, required=True, help='Host to connect to')
   # args = parser.parse_args()
    raddr = (sys.argv[1],sys.argv[1])
    main(raddr)
