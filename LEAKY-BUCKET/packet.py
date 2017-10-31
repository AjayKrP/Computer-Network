import pickle
import time
import random
BUCKET_SIZE = 10

class Packet:
    _packet_types = ['A', 'D', 'C', 'H']

    def __init__(self, ptype, seq_no, data=None):

        assert ptype in Packet._packet_types
        assert type(seq_no) is int

        self.seq_no = seq_no
        self.ptype = ptype
        self.data = data

    def __str__(self):
        return 'SEQ : {}, PTYPE : {}, DATA : {}'.format(self.seq_no, self.ptype, self.data)


def send_ack(expected_seq, sock, addr):
    na_packet = Packet(ptype='A', seq_no=expected_seq)
    sock.sendto(pickle.dumps(na_packet), addr)


def send_data(expected_seq, sock, addr, data):
    d_packet = Packet(ptype='D', seq_no=expected_seq, data=data)
    sock.sendto(pickle.dumps(d_packet), addr)


def send_close(expected_seq, sock, addr):
    c_packet = Packet(ptype='C', seq_no=expected_seq)
    sock.sendto(pickle.dumps(c_packet), addr)


def send_hello(expected_seq, sock, addr):
    c_packet = Packet(ptype='H', seq_no=expected_seq)
    sock.sendto(pickle.dumps(c_packet), addr)

def get_time():
        return random.randint(1, 10)

def display_buffer(i):
    if i != 10:
        print('Buffer Size : ', i* 100)


def prepare_sending():
    time.sleep(random.random() * 2)


BUFFER_SIZE = 1024
QUEUE_TIMEOUT = 0.1
SLEEP_TIMER=0.5
ENQUEUE_SIZE = 2
LISTEN_PORT = 8081
