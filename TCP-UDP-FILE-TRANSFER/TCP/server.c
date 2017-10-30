#include <stdio.h>
#include <netinet/in.h>
#include <memory.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <zconf.h>

#define BUFFERT 512
struct sockaddr_in sock_addr, cli_addr;
int create_server(int port){
    int yes = 1;
    int l = sizeof(struct sockaddr_in);
    int sfd;
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0 ){
        perror("Error first");
    }
    bzero(&sock_addr, l);
    if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
        perror("Error second");
    }
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sfd, (struct sockaddr*)&sock_addr,  l) < 0){
        perror("Error third");
    }
    return sfd;
}


int main(int argc, char** argv){
    unsigned int length = sizeof(struct sockaddr_in);
    int fd, sfd;
    int clt_port;
    char buffer[BUFFERT], filename[256];
    char dst[INET6_ADDRSTRLEN];
    int nsid;
    if(argc < 2){
        perror("Error fourth");
    }

    sfd = create_server(atoi(argv[1]));
    bzero(&buffer, BUFFERT);
    listen(sfd, 10);
    nsid = accept(sfd, (struct sockaddr*)&cli_addr, &length);
    if(nsid < 0){
        perror("Error fifth");
    } else{
        if(inet_ntop(AF_INET,&cli_addr.sin_addr,dst,INET_ADDRSTRLEN) == NULL){
            perror("Error");
        }
        clt_port = htons(cli_addr.sin_port);
         bzero(filename,256);
         sprintf(filename,"clt.%d",clt_port);
         printf("Creating the copied output file : %s\n",filename);

         if ((fd=open(filename,O_CREAT|O_WRONLY,0600))==-1)
         {
          perror("open fail");
          exit (3);
          }

        bzero(buffer,BUFFERT);
        int n = (int) recv(nsid, buffer, BUFFERT, 0);
        while (n){
            if (n == -1){
                perror("Error seventh");
            }
            int m = write(fd, buffer, n) < 0;
            if(m){
                perror("Error sdfsdf");
            }
            n = (int) recv(nsid, buffer, BUFFERT, 0);
        }
    }
    close(nsid);
    close(fd);
    close(sfd);
    printf ("End of transmission with%s.%d \n", dst, clt_port);
}