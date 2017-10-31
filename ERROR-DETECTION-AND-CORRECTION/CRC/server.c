#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "packet.h"


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage - %s <ip> <port> \n", argv[0]);
        return -1;
    }
    struct sockaddr_in client,server;
    packet received_message;
    char ip[INET_ADDRSTRLEN];
    int client_size = sizeof(client);
    int sock = socket(AF_INET , SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("Failed to create the socket\n");
        return -1;
    }
    server.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1] , &server.sin_addr);
    server.sin_port = htons(atoi(argv[2]));
    if(bind(sock,(struct sockaddr *)&server, sizeof(struct sockaddr) ) < 0) {
        perror("Failed to bind on this port");
        return -1;
    }
    else {
        printf("Listening on %s:%s\n",argv[1],argv[2]);
    }
    while(1){
        if(recvfrom(sock,&received_message,sizeof(packet),0,(struct sockaddr *)&client,(unsigned int *)&client_size) < 0) {
            perror("Failed to receive the message");
        }
        else {
            inet_ntop(AF_INET, &client.sin_addr , ip, INET_ADDRSTRLEN);
            printf("Received %lu bytes message from %s\n", strlen(received_message.message), ip);
            printf("Message : %s\nCRC Checksum : 0x%x\n", received_message.message , received_message.crc_checksum);
            if(calc_crc(received_message.message) == received_message.crc_checksum ) {
                printf("CRC Verified.\n");
            }
            else {
                perror("CRC Verification Failed.\n");
            };
        }
    }

}
