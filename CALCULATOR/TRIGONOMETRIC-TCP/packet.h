
#ifndef TRIGCALC_PACKET_H
#define TRIGCALC_PACKET_H

#define PORT 8089
#define HOST "127.0.0.1"

enum trig_operation{ sin_t, cos_t, tan_t };

struct calculate {
    double angle;
    trig_operation op;
};
struct result {
    bool success;
    double value;
};

#endif //TRIGCALC_PACKET_H
