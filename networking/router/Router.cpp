#include "Router.hpp"
#include "../IotDCP/HttpResponses.hpp"
#include <iostream>

Router::Router() {}

void Router::AddPath(std::string path, std::function<std::string(Payload)> handler) {
    m_routes.emplace(path, handler);
}

std::function<std::string(Payload)> Router::GetPathHandler(std::string &path) {
    auto handler = m_routes.find(path);
    if (handler != m_routes.end())
        return handler->second;
    return nullptr;
}

std::string Router::GetPathHandlerResponse(std::string request) {
    std::string path = GetPath(request);
    std::function<std::string(Payload)> handler
        = GetPathHandler(path);
    if (handler)
        return handler(Payload(request));
    return "";
}

std::string Router::GetPath(std::string request) {
    std::string path;
    bool pathB = false;
    for (int it = 0; it < request.length(); it++) {
        if (pathB == true)
            path.push_back(request[it]);

        if ((request[it] == ' ' || request[it] == '?') && pathB ) {
            path.pop_back();
            break;
        }

        if (request[it] == ' ') {
            pathB = true;
        }
    }
    return path;
}

