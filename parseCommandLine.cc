#include <unistd.h>
#include "socketOp.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

int parseCommandLine(int argc, char *argv[], Options &options){
    int opt = 0;
    while((opt = getopt(argc, argv, "scl:n:p:i:")) != -1){
        switch(opt){
            case 's':
                options.isServer = true;
                break;
            case 'c':
                options.isClient = true;
                break;
            case 'l':
                options.length = atoi(optarg);
                break;
            case 'n':
                options.num = atoi(optarg);
                break;
            case 'p':
                options.port = static_cast<int>(atoi(optarg));
                break;
            case 'i':
                options.ip = std::string(optarg);
                break;
            default:
                break;
        }
    }

    if(options.port < 1024){
        std::cerr<<"please spicify a legal port\n";
        return -1;
    }

    if(options.isClient && options.isServer){
        std::cerr<<"the program should either be a client or a server\n";
        return -1;
    }

    if(options.isServer){
        if(options.ip.size() != 0){
            std::cerr<<"you don't need to assign an ip for server\n";
            std::cerr<<"asssign host ip defaultly\n";
            return 1;
        }
    }

    if(options.isClient){
        if(options.ip.size() == 0){
            std::cerr<<"please assign server ip\n";
            return -1;
        }
    }
}