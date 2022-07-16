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
