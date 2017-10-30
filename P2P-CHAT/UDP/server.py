import socket
udp_ip = '127.0.0.1'
udp_port = 8014
fd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
fd.bind((udp_ip,udp_port))
while True:
    r = fd.recvfrom(1000)
    msg = str(r[0], 'utf-8')
    print("client : %s"%(msg))
    reply = input('server : ')
    client_address = r[1]
    fd.sendto(bytearray(reply, "utf-8"), client_address)