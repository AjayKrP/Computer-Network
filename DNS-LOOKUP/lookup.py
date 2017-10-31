import socket

if __name__=="__main__":
    ip_addr = input("Enter the domain name: ")
    print(socket.gethostbyname(ip_addr))
    address = socket.gethostbyname(ip_addr)
    print(socket.gethostbyaddr(address))
    print(socket.gethostname())
