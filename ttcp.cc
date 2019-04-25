#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <memory>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>

#include <assert.h>

#include "socketOp.h"
#include "ttcp.h"

int transmit(Options &options){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("transmint sockfd create failed");
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_addr.s_addr = inet_addr(options.ip.c_str());
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(options.port);

    if((connect(sockfd, (sockaddr*)&serverAddr, sizeof(sockaddr))) != 0){
        perror("connect in tranmit");
        return -1;
    }

    Session taskSession(options.num, options.length);
    Session ackSession;
    writeN(sockfd, &taskSession, sizeof(Session));
    readN(sockfd, &ackSession, sizeof(Session));

    assert(taskSession.length == ackSession.length && taskSession.num == ackSession.num);

    Payload *payload = (Payload*)::malloc(4+options.length);
    for(int i = 0; i < options.length; ++i){
        payload->data[i] = "0123456789abcdefghijklmnopqrstuvwxyz"[i%36];
    }

    for(int i = 0; i < options.num; ++i){
        writeN(sockfd, payload, 4+options.length);
        readN(sockfd, &ackSession, sizeof(Session));
        assert(ackSession.length == options.length);

    }

    close(sockfd);

    std::cout<<"Client: Package Length is "<<options.length<<", ";
    std::cout<<"sent "<<options.num<<" packages"<<std::endl;
    return 1;
}

int receive(Options &options){

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("socket in receive fail");
        exit(1);
    }

    sockaddr_in *serverAddr = (sockaddr_in*)::malloc(sizeof(struct sockaddr_in));
    serverAddr->sin_addr.s_addr = inet_addr(options.ip.c_str());
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(options.port);
    
    int result = bind(sock, (struct sockaddr*)serverAddr, sizeof(struct sockaddr_in));
    if(result != 0){
        perror("bind");
        exit(1);
    }

    listen(sock, 5);

    socklen_t *len = (socklen_t*)::malloc(sizeof(socklen_t));
    *len = sizeof(struct sockaddr_in);
    int clientFd = accept(sock, (struct sockaddr*)serverAddr, len);
    if(clientFd < 0){
        perror("accept");
        exit(1);
    }

    
    Session *taskSession = new Session();

    readN(clientFd, taskSession, sizeof(Session));

    Session *ackSesion = new Session(taskSession->num, taskSession->length);

    writeN(clientFd, ackSesion, sizeof(Session));

    Payload *payload = (Payload*)::malloc(4+taskSession->length);
    
    timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < options.num; ++i){
        int ret = readN(clientFd, payload, 4+options.length);
        assert(ret == options.length+4);

        ret = writeN(clientFd, ackSesion, sizeof(Session));
        assert(ret == sizeof(Session));
    }
    gettimeofday(&end, NULL);
    double timeInMS = 1000*(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000.0;
    std::cout<<"send "<<options.num * options.length<<" bytes in "


}
