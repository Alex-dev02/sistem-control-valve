#include "Thermostat.h"
#include "../../networking/http/HTTP.h"
#include "../../networking/router/Router.h"
#include "../../networking/http/Payload.h"

#include <iostream>

std::string root(Payload payload) {
    return "Home";
}

Thermostat::Thermostat(std::string PORT, int BACKLOG)
{
    Router router;
    router.addPath("/", &root);
    Socket server(PORT, BACKLOG);
    while (true) {
        std::string req = server.accept_new_connection();
        std::cout << '\n' << req << '\n';
        server.respond_to_request(HTTP::getHTTPResponse(req));
    }
}

