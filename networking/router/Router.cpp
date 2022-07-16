#include "Router.hpp"

Router::Router() {}

void Router::addPath(std::string path, std::function<std::string(Payload)> handler) {
    routes.emplace(path, handler);
}

std::function<std::string(Payload)> Router::getPathHandler(std::string &path) {
    auto handler = routes.find(path);
    if (handler != routes.end())
        return handler->second;
    return nullptr;
}
