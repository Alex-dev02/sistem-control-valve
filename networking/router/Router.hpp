#pragma once

#include <unordered_map>
#include <functional>

#include "../IotDCP/Payload.hpp"


// The route handler should return a string, representing the data
// returned by the path handler
// The input string should be either the payload for a POST function
// Or the variables transmited through the path with 
// ex: /myPath/temp?new=15 -> std::string("new=15");

class Router {
public:
    Router();
    void AddPath(std::string path, std::function<std::string(Payload)>);
    std::string GetPathHandlerResponse(std::string request);
private:
    std::unordered_map<std::string, std::function<std::string(Payload)>> m_routes;

    std::function<std::string(Payload)> GetPathHandler(std::string &path);
    std::string GetPath(std::string request);
};