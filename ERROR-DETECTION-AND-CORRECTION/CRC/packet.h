#include <stdint.h>
#include <string.h>

#ifndef CRC_SOCKETS_PACKET_H
#define CRC_SOCKETS_PACKET_H
#define MAX_MESSAGE 256

#define WIDTH 32
#define MSB (1 << (WIDTH - 1))
#define POLYNOMIAL 0x93b39b1b

struct packet {
    char message[MAX_MESSAGE];
    uint32_t  crc_checksum;
};

typedef struct packet packet;

uint32_t calc_crc(char message[]) {
    uint32_t remainder = 0;
    int length = strlen(message);

    for(int i = 0 ; i < length; ++i) {
        remainder ^= (message[i] << (WIDTH - 8));
        for(int j = 0 ; j < 8; ++j) {
            if(remainder&MSB) {
                remainder = (remainder << 1 ) ^ POLYNOMIAL;
            }
            else {
                remainder = remainder << 1;
            }
        }
    }
    return remainder;
}

#endif //CRC_SOCKETS_PACKET_H
