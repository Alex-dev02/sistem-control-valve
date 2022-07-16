#include <string>

namespace HttpResponses{
    std::string OK() {
        return
            "HTTP/1.1 200 OK\n" 
            "Content-Type: text/plain\n" 
            "Content-Length: 0\n\n";
    }
    std::string NotFound() {
        return "HTTP/1.1 404 Not Found\n\n";
    }
    std::string ServerError() {
        return "HTTP/1.1 500 Internal Server Error\n\n";
    }
}