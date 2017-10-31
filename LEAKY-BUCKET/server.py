import socket
from packet import send_ack
import threading
import time
import pickle
import queue
from queue import Queue
from packet import *
from packet import *
_sentinal = object()


def empty_from_buffer(param, q=None):
    if not q: pass
    else : q.pop(param)


def check_incoming(pipeline, sock):

    assert type(pipeline) == Queue
    while True:
        try:
            raw_data, addr = sock.recvfrom(2048)
            r_packet = pickle.loads(raw_data)
            if r_packet.ptype == 'C':
                pipeline.put(_sentinal)
                print('check_incoming() exiting...')
                break
            if r_packet.ptype == 'D':
                pipeline.put(r_packet.data, block=False, timeout=QUEUE_TIMEOUT)

                empty_from_buffer(10240)


                display_buffer(pipeline.qsize())
                send_ack(r_packet.seq_no, sock, addr)
        except queue.Full:
                pass
            # print('Bucket full, Packet Dropped')
    print('check_incoming() exited...')

def leak_bucket(pipeline, recv_list):
    while True:
        try:
            time.sleep(SLEEP_TIMER)
            for _ in range(ENQUEUE_SIZE):
                top = pipeline.get(block=False)
                if top is not _sentinal:
                    recv_list.append(top)
                else:
                    print('Transfer Complete')
                    print('leak_bucket() finishing up')
                    return
        except queue.Empty:
            pass # Bucket Empty

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    print('Receiving the data in the range of 20 Kbps')
    sock.bind(('127.0.0.1', 8081,))
    recv_list = []
    pipeline = Queue(maxsize=BUCKET_SIZE)
    incoming_t = threading.Thread(target=check_incoming, args=(pipeline, sock,))
    consume_t = threading.Thread(target=leak_bucket, args=(pipeline, recv_list,))
    incoming_t.start()
    consume_t.start()
    incoming_t.join()
    consume_t.join()
    print('Data Length -> {}\nData -> {}\n'.format(len(recv_list), recv_list))

if __name__ == '__main__':
    main()





