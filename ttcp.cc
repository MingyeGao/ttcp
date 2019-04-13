#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

struct Session{
    int32_t num;
    int32_t length;
}__attribute__((__packed__));

struct Payload{
    int32_t length;
    char data[0];
};

int main(int argc, char *argv[]){
    bool isServer = true;
    int payloadLength = 8192;
    int sessionNum = 1024;
    int opt = 0;
    while((opt = getopt(argc, argv, "scl:n:")) != -1){
        switch(opt){
            case 's':
                isServer = true;
                break;
            case 'c':
                isServer = false;
                break;
            case 'l':
                payloadLength = atoi(optarg);
                break;
            case 'n':
                sessionNum = atoi(optarg);
                break;
        }
    }

    std::cout<<"payloadLength = "<<payloadLength<<std::endl;
    std::cout<<"sessionNum = "<<sessionNum<<std::endl;
    //std::cout<<"payloadLength = "<<<payloadLength<<std::endl;

}

void createServer(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(socket < 0){

    }
}