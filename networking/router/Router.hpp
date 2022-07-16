#pragma once

#include <unordered_map>
#include <functional>

#include "../http/Payload.hpp"


// The route handler should return a string, representing the data
// returned by the handler
// The input string should be either the payload for a POST function
// Or the variables transmited through the path with GET/PUT
// ex: /myPath/temp?new=15 -> std::string("new=15");

class Router {
public:
    Router();
    void addPath(std::string path, std::function<std::string(Payload)>);
    std::function<std::string(Payload)> getPathHandler(std::string &path);
private:
    std::unordered_map<std::string, std::function<std::string(Payload)>> routes;
};