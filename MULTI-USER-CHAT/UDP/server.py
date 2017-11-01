import socket
import argparse
import pickle
import sys
from packet import Packet

connected_users = []

def broadcast_message(message):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    msg_packet = Packet(ptype='M', data=message)
    for addr in connected_users:
        sock.sendto(pickle.dumps(msg_packet), addr)




def main(port):
    global connected_users

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(('', port))
    while True:
        data, addr = sock.recvfrom(1024*10)
        recv_packet = pickle.loads(data)
        if recv_packet.ptype == 'H':
            connected_users.append(addr)
        elif recv_packet.ptype == 'C':
            connected_users.remove(addr)
        elif recv_packet.ptype == 'M':
            broadcast_message(recv_packet.data)




if __name__ == '__main__':
   # parser = argparse.ArgumentParser(description='Multi user chat with UDP')
   # parser.add_argument('--port', type=int, required=True, help='Port to listen on')
   # args = parser.parse_args()
   # print('Started Chat server on 0.0.0.0:{}'.format(args.port))
    main(int(sys.argv[1]))
