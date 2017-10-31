#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "packet.h"
using namespace std;
int main() {
    calculate c;
    int choice;
    result r;

    printf("Which operation ( 1 - sin, 2 - cos, 3 - tan) ? ");
    scanf("%d", &choice);
    printf("%d your chose\n", choice);
    switch(choice){
        case 1:
            c.op = sin_t;
            break;
        case 2:
            c.op = cos_t;
            break;
        case 3:
            c.op = tan_t;
        default:
            cout << "No valid choice, goodbye cruel world" << endl;
            return -1;
    }
    printf("Angle ? ");
    scanf("%lf", &c.angle);

    sockaddr_in client{0,};
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    inet_pton(AF_INET, HOST, &client.sin_addr);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock, reinterpret_cast<const sockaddr *>(&client), sizeof(sockaddr));
    send(sock,&c, sizeof(calculate), 0);
    recv(sock, &r, sizeof(result), 0);
    if(r.success) cout << "Result = " << r.value << endl;
    else cout << "Exception" << endl;
    close(sock);
}