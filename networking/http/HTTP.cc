#include "HTTP.h"
#include "../router/Router.h"

#include <functional>

std::string HTTP::getNotFoundCode() {
    return "404 Not Found";
}

std::string HTTP::getContentType(std::string type) {
    return "Content-Type: " + type;
}

std::string HTTP::generateResponse(
    std::string httpVersion,
    std::string responseCode,
    std::string contentType,
    std::string content)
{
    return httpVersion + " " + responseCode
        + "\r\n" + "Content-Length: " + std::to_string(content.length()) +
        + "\r\n" + contentType + "\r\n\r\n" + content; 

}

std::string HTTP::getHTTPResponse(std::string &path, std::string httpVersion){ 
    class Router router;
    std::function<std::string(std::string)> handler
        = router.getPathHandler(path);
    if (!handler)
        return generateResponse(httpVersion, getNotFoundCode(), getContentType());
}
