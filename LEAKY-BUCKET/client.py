import socket
from packet import send_data, send_close
import random, time, pickle
import threading
from packet import *

listening = True
total_acked = 0

def listen_ack(sock):
    global total_acked
    while listening:
        raw_data, _ = sock.recvfrom(2048)
        ack_packet = pickle.loads(raw_data)
        if ack_packet.ptype == 'A':
            total_acked += 1
            #print('Ack Received for ', ack_packet.seq_no)


def main(raddr, data):
    global listening
    port = random.randint(1000,2**16 -1)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    laddr = ('127.0.0.1', port,)
    sock.bind(laddr)
    print('Sending the data in the range of 10 - 30 Kbps')
    print('Trying to send {} packets to {}'.format(len(data), raddr))
    ack_t = threading.Thread(target=listen_ack,args=(sock,))
    ack_t.start()
    i = 0
    send_data(i, sock, raddr, data[i])
    i += 1

    while i < len(data):
        prepare_sending()
        try :
            for k in range(get_time()):
                sending_rate = random.randint(10, 30)
                print('Sending At ', sending_rate )
                send_data(i, sock, raddr, data[i])
                i += 1
        except IndexError:
            break

    listening = False
    ack_t.join()
    print('Data sent')
    #if total_acked != len(data):
     #   print('Receiver lost {} packets because bucked was full'.format(len(data) - total_acked))
    send_close(i+1, sock, raddr)


if __name__ == '__main__':
    data = "There really is a Linux, and these people are using it, but it is just a part of the system they use." \
           " Linux is the kernel: the program in the system that allocates the machine's resources to the other programs " \
           "that you run. The kernel is an essential part of an operating system, but useless by itself; it can only function" \
           " in the context of a complete operating system. Linux is normally used in combination with the GNU operating system:" \
           " the whole system is basically GNU with Linux added, or GNU/Linux. All the so-called Linux distributions are really " \
           "distributions of GNU/Linux!"

    main(('127.0.0.1',8081,), data.split(' '))
