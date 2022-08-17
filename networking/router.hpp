#pragma once

#include <unordered_map>
#include <functional>

#include "request.hpp"
#include "response.hpp"

// The route handler should return a string, representing the data
// returned by the path handler
// The input string should be either the payload for a POST function
// Or the variables transmited through the path with 
// ex: /myPath/temp?new=15 -> std::string("new=15");

class Router {
public:
    Router();
    bool AddPath(std::string path, std::function<Response(Request)>);
    Response GetResponse(const Request& request);
private:
    Router(const Router&);
    Router& operator=(const Router&);
    
    std::unordered_map<std::string, std::function<Response(Request)>> m_routes;
};