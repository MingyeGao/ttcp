#ifndef SOCKETOP_H
#define SOCKETOP_H

#include <string>

int readN(int sockfd, void *buffer, int size);
int writeN(int sockfd, void *buffer, int size);

struct Options{
    Options():num(1000), length(8192), isServer(true), isClient(false), port(-1), ip(""){};
    int num;
    int length;
    bool isServer, isClient;
    short port;
    std::string ip;
};

#endif