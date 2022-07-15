#include "Router.hpp"

Router::Router() {
    // here should go all the available routes and their path
    // ex: routes.emplace("/home", &home);
    // &home being the pointer to a function called "home"
}

void Router::addPath(std::string path, std::function<std::string(Payload)> handler) {
    routes.emplace(path, handler);
}

std::function<std::string(Payload)> Router::getPathHandler(std::string &path) {
    auto handler = routes.find(path);
    if (handler != routes.end())
        return handler->second;
    return nullptr;
}

std::unordered_map<std::string, std::function<std::string(Payload)>>
    Router::routes = {};
