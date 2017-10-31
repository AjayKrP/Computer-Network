
#ifndef TRIGCALC_PACKET_H
#define TRIGCALC_PACKET_H

#define PORT 8089
#define HOST "127.0.0.1"

enum trig_operation{ add, sub, mul, divi};

struct calculate {
    double val1;
    double val2;
    trig_operation op;
};
struct result {
    bool success;
    double value;
};

#endif //TRIGCALC_PACKET_H