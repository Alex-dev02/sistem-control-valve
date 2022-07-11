#include <iostream>

#include "thermostat.cc"
#include "../../networking/router/Router.h"

std::string f(std::string str) {
    return str;
}

int main() {
    Router r;
    std::string path = "/r";
    r.addPath(path, &f);
    std::cout << "Hello from Thermostat\n";
}