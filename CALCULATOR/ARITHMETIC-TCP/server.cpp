#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cmath>


#include "packet.h"

result trig_calculate(calculate c);

using namespace std;
int main() {
    calculate c{0,};

    sockaddr_in client{0,}, server{0,};
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, HOST, &server.sin_addr);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock, reinterpret_cast<const sockaddr *>(&server), sizeof(sockaddr));
    listen(sock, 10);
    while(true) {
        socklen_t len;
        int client_fd = accept(sock, reinterpret_cast<sockaddr *>(&client), &len);
        while(true) {
            int rd = recv(client_fd, &c, sizeof(calculate), 0);
            if(!rd) break;
            result r = trig_calculate(c);
            send(client_fd, &r, sizeof(r), 0);
        }
    }
}

result trig_calculate(calculate c) {
    result r = { success : true, value : 0};
    switch(c.op) {
        case add:
            r.value = c.val1 + c.val2;
            break;
        case sub:
            r.value = c.val1 - c.val2;
            break;
        case mul:
            r.value = c.val1 * c.val2;
            break;
        case divi:
            if(c.val2 == 0.0) r.success = false;
            else r.value = c.val1/c.val2;
            break;
    }
    return r;
}