#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "packet.h"


int main(int argc, char **argv) {
    if(argc != 4) {
        printf("usage - %s <ip> <port> <message>\n",argv[0]);
        return -1;
    }
    struct sockaddr_in client;
    packet current_message;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("failed to create socket\n");
        return -1;
    }

    client.sin_family = AF_INET;
    inet_pton(AF_INET , argv[1] ,  &client.sin_addr);
    client.sin_port = htons(atoi(argv[2]));

    strncpy(current_message.message,argv[3],MAX_MESSAGE);
    current_message.crc_checksum = calc_crc(current_message.message);
    printf("sending to %s:%s , message size = %lu ", argv[1], argv[2], strlen(argv[3]));

    if(sendto(sock,&current_message,sizeof(packet), 0, (struct sockaddr *)&client, sizeof(client)) < 0) {
        perror("error sending the packet");
    }

    close(sock);
    return 0;
}
