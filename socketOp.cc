#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

int readN(int sockfd, void *buffer, int size){
    int readNum = 0, totalNum = 0;
    while((readNum = read(sockfd, reinterpret_cast<void*>(reinterpret_cast<size_t>(buffer)+totalNum), size)) > 0){
        totalNum += readNum;
    }
    
    if(totalNum == size){
        return totalNum;
    }
    else{
        return -1;
    }
}

int writeN(int sockfd, void *buffer, int size){
    int writeNum = 0, totalNum = 0;
    while((writeNum = write(sockfd, buffer+totalNum, size-totalNum)) > 0){
        totalNum += writeNum;
        break;
    }


    if(totalNum == size){
        printf("totalNum  is %d\n", totalNum);
        return totalNum;
    }
    else{
        perror("writeN");
        return -1;
    }
}

//void transmit()
