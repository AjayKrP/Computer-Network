//
// Created by ajay on 10/30/17.
//

#include <netinet/in.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <fcntl.h>
#include <zconf.h>

#define BUFFERT 512

struct sockaddr_in sock_addr, cli_addr;

int create_server_socket(int port){
    int sfd, l;
    l = sizeof(struct sockaddr_in);
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sfd < 0){
        perror("Unable to create socket!!!");
    }
    bzero(&sock_addr, l);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = htons(INADDR_ANY);
    if(bind(sfd, (struct sockaddr*)&sock_addr, l) < 0){
        perror("Unable to bind!!!");
    }
    return sfd;
}

int main(int argc, char**argv){
    //Descriptor
    int fd, sfd;
    char buf[BUFFERT];
    off_t count=0, n; // long type
    char filename[256];
    unsigned int l = sizeof(struct sockaddr_in);

    if(argc != 2){
        perror("Argument error!!!");
    }

    sfd = create_server_socket(atoi(argv[1]));
    bzero(filename,256);
    sprintf(filename,"clt.%d",atoi(argv[1]));
    printf("Creating the output file : %s\n",filename);

    if((fd=open(filename, O_CREAT|O_WRONLY|O_TRUNC,0600))==-1){
        perror("open fail");
        return EXIT_FAILURE;
    }

    bzero(buf, BUFFERT);
    n = recvfrom(sfd, buf, BUFFERT, 0, (struct sockaddr*)&cli_addr, &l);
    while (n){
        if (n == -1){
            perror("Unable to receive!!!");
        }
        int m = (int) write(fd, buf, BUFFERT);
        if(m < 0){
            perror("unable to write!!!");
        }
        count += m;
        n = recvfrom(sfd, buf, BUFFERT, 0, (struct sockaddr*)&cli_addr, &l);
    }

    printf("Number of bytes transferred : %lld \n",count);

    close(sfd);
    close(fd);
    return EXIT_SUCCESS;
}