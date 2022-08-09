#pragma once

#include "valve.hpp"

#include <networking/router.hpp>
#include <networking/request.hpp>
#include <networking/response.hpp>

class ValveRouter {
public:
    ValveRouter(std::string ip_address, std::string port);

    Response GetResponse(const Request& request);
private:
    Router m_router;
    Valve m_valve;

    std::string m_ip_address;
    std::string m_port;

    Response Connect(Request request);
    Response SetCurrentTargetRoute(Request request);
};
