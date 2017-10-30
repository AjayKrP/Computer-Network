//
// Created by ajay on 10/30/17.
//

#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <memory.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <zconf.h>

#define BUFFERT 512

struct sockaddr_in sock_addr;
int create_client(int port, char* ipaddr){
    int l = sizeof(struct sockaddr_in);
    int sfd;
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sfd < 0){
        perror("can\'t create socket!!!\n");
    }
    bzero(&sock_addr, l);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    if(inet_pton(AF_INET, ipaddr, &sock_addr.sin_addr) == 0){
        perror("Invalid ip address!!!");
    }
    return sfd;
}
int main(int argc, char**argv){
    int sfd,fd;
    char buf[BUFFERT];
    off_t count=0, m,sz;//long
    long int n;
    int l=sizeof(struct sockaddr_in);
    struct stat buffer;

    if(argc != 4){
        perror("Argument Error!!!");
    }

    sfd = create_client(atoi(argv[2]), argv[1]);

    if((fd = open(argv[3], O_RDONLY, 0600)) == -1){
        perror("Unable to open file!!!\n");
    }
    if(stat(argv[3], &buffer) == -1){
        perror("stat failed!!!");
    }
    else
        sz = buffer.st_size;

    bzero(buf, BUFFERT);

    n = read(fd, buf, BUFFERT);
    while (n){
        if(n == -1){
            perror("Read failed");
        }
        m = sendto(sfd, buf, n, 0, (struct sockaddr*)&sock_addr, l);
        if(m==-1){
            perror("send error");
            return EXIT_FAILURE;
        }
        count += m;
        bzero(buf, BUFFERT);
        n = read(fd, buf, BUFFERT);
    }

    m = sendto(sfd, buf, 0, 0, (struct sockaddr*)&sock_addr, l);
    printf ("Number of bytes transferred:% lld \n", count);
    printf ("On a total size of:% lld \n", sz);
}


