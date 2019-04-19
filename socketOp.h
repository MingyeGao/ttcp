#ifndef SOCKETOP_H
#define SOCKETOP_H

int readN(int sockfd, void *buffer, int size);
int writeN(int sockfd, void *buffer, int size);

struct Options{
    Options():num(0), length(0), isServer(true), isClient(false){}
    int num;
    int length;
    bool isServer, isClient;
};

#endif