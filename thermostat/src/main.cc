#include <iostream>
#include "thermostat.cc"
#include "../../networking/socket/Socket.h"

int main(int argc, char *argv[]) {
    
    Socket s(
        argc >= 2 ? std::to_string(std::stoi(argv[1])) : "4000",
        argc >= 3 ? std::stoi(argv[2]) : 10
    );
}