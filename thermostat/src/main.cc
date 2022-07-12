#include <iostream>

#include "../../networking/socket/Socket.h"
#include "../../networking/router/Router.h"
#include "Thermostat.h"

int main(int argc, char *argv[]) {
    
    Thermostat t(
        argc >= 2 ? std::to_string(std::stoi(argv[1])) : "4000",
        argc >= 3 ? std::stoi(argv[2]) : 10
    );
}