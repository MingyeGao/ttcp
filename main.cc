#include <iostream>
#include "socketOp.h"
#include "parseCommandLine.h"

int main(int argc, char *argv[]){

    Options options;

    parseCommandLine(argc, argv, options);
}