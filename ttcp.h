#ifndef TTCP_H
#define TTCP_H
#include <cstdlib>
#include "socketOp.h"

struct Session{
    int32_t num;
    int32_t length;
    Session(int32_t _num, int32_t _len):num(_num), length(_len){};
    Session(){};
}__attribute__((__packed__));

struct Payload{
    int32_t length;
    char data[0];
};

int transmit(Options &options);
int receive(Options &options);


#endif