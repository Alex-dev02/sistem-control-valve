#include "HttpResponses.hpp"


std::string HttpResponses::OK(std::string content) {
    return
        "HTTP/1.1 200 OK\n" 
        "Content-Type: text/plain\n" 
        "Content-Length: " + std::to_string(content.length()) +
        (content.length() == 0 ? "\n\n" : "\n\n" + content + "\n");
        ;
}
std::string HttpResponses::NotFound() {
    return "HTTP/1.1 404 Not Found\n\n";
}
std::string HttpResponses::ServerError() {
    return "HTTP/1.1 500 Internal Server Error\n\n";
}

// This response would always come from the valves
// so it's safe to search only for the OK code
// at least for now
bool HttpResponses::IsResponseASuccess(std::string http_request) {
    if (http_request.find("OK") == std::string::npos)
        return false;
    return true;
}
