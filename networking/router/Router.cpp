#include "Router.hpp"

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
