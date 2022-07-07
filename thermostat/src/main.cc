#include <iostream>
#include "thermostat.cc"
#include "../../networking/socket/Socket.h"

int main() {
    Socket s("4000", 10, "alex-VirtualBox");
}