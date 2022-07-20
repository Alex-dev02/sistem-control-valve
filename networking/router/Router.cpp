#include "Router.hpp"

#include <iostream>

Router::Router() {}

void Router::AddPath(std::string path, std::function<Response(Request)> handler) {
    m_routes.emplace(path, handler);
}

Response Router::GetResponse(Request request) {
    auto handler = m_routes.find(request.GetPath());
    if (handler != m_routes.end())
        return (handler->second)(request);
    // vezi ca aici trb lucrat mai mult
    return Response(Response::HttpNotFound);
}
