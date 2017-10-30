#include <stdio.h>
#include <netinet/in.h>
#include <memory.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <zconf.h>
#include <sys/stat.h>

#define BUFFERT 512
struct sockaddr_in sock_addr;


int create_client_socket(int port, char* ipaddr){
    int sfd;
    int l = sizeof(struct sockaddr_in);
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0){
        perror("Can't create socket!!!");
    }
    bzero(&sock_addr, l);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    if(inet_pton(AF_INET, ipaddr, &sock_addr.sin_addr) == -1){
        perror("invalid ip address!!!");
    }
    return sfd;
}


int main(int argc, char** argv){
    int sfd,fd;
    char buf[BUFFERT];
    off_t count=0, m,sz;//long
    long int n;
    int l=sizeof(struct sockaddr_in);
    struct stat buffer;

    if(argc != 4){
        perror("Invalid argument!!!\n");
    }

    sfd = create_client_socket(atoi(argv[2]), argv[1]);

    if ((fd = open(argv[3],O_RDONLY))==-1){
        perror("open fail");
        return EXIT_FAILURE;
    }

    //file size
    if (stat(argv[3],&buffer)==-1){
        perror("stat fail");
        return EXIT_FAILURE;
    }
    else
        sz=buffer.st_size;
    bzero(&buf,BUFFERT);

    if(connect(sfd,(struct sockaddr*)&sock_addr,l)==-1){
        perror("connection error\n");
        exit (3);
    }

    n=read(fd,buf,BUFFERT);
    while(n){
        if(n==-1){
            perror("read fails");
            return EXIT_FAILURE;
        }
        m=sendto(sfd,buf,n,0,(struct sockaddr*)&sock_addr,l);
        if(m==-1){
            perror("send error");
            return EXIT_FAILURE;
        }
        count+=m;
        //fprintf(stdout,"----\n%s\n----\n",buf);
        bzero(buf,BUFFERT);
        n=read(fd,buf,BUFFERT);
    }
    // read just returned 0: end of file
    // to unlock the serv
    m = sendto(sfd,buf,0,0,(struct sockaddr*)&sock_addr,l);

    printf ("Number of bytes transferred:% lld \n", count);
    printf ("On a total size of:% lld \n", sz);
    close(sfd);
    return EXIT_SUCCESS;
}
