#include <iostream>
#include "socketOp.h"
#include "parseCommandLine.h"
#include "ttcp.h"
#include <assert.h>

int main(int argc, char *argv[]){

    if(argc < 2){
        std::cout<<"usage:\n";
        std::cout<<"as a server: ./ttcp [-s] -p [port] -i [ip]\n";
        std::cout<<"as a client: ./ttcp [-c] -p [port] -i [ip] [-n] [package num] [-l] [package length]\n";
        exit(1);
    }

    Options options;

    parseCommandLine(argc, argv, options);

    if(options.isClient){
        transmit(options);
    }
    else if(options.isServer){
        receive(options);
    }
    else{
        assert(0);
    }
}