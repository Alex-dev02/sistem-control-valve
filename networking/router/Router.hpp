#pragma once

#include <unordered_map>
#include <functional>

#include "../communication/Request.hpp"
#include "../communication/Response.hpp"

// The route handler should return a string, representing the data
// returned by the path handler
// The input string should be either the payload for a POST function
// Or the variables transmited through the path with 
// ex: /myPath/temp?new=15 -> std::string("new=15");

class Router {
public:
    Router();
    bool AddPath(std::string path, std::function<Response(Request)>);
    Response GetResponse(Request request);
private:
    std::unordered_map<std::string, std::function<Response(Request)>> m_routes;
};