#pragma once

#include "valve.hpp"

#include <networking/router.hpp>
#include <networking/request.hpp>
#include <networking/response.hpp>

class ValveRouter {
public:
    ValveRouter();

    Response GetResponse(const Request& request);

    Valve& GetValve();
private:
    Router m_router;
    Valve m_valve;

    Response Ping(Request request);
    Response SetCurrentTargetRoute(Request request);
};
