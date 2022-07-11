#include "HTTP.h"
#include "../router/Router.h"

#include <functional>

std::string HTTP::getNotFoundCode() {
    return "404 Not Found";
}

std::string HTTP::getOKCode() {
    return "200 OK";
}

std::string HTTP::getContentType(std::string type) {
    return "Content-Type: " + type;
}

std::string HTTP::generateHTTPResponse(
    std::string httpVersion,
    std::string responseCode,
    std::string contentType,
    std::string content)
{
    return httpVersion + " " + responseCode
        + "\r\n" + "Content-Length: " + std::to_string(content.length()) +
        + "\r\n" + contentType + "\r\n\r\n" + content; 

}

std::string HTTP::getHTTPResponse(std::string &path, Payload payload, std::string httpVersion){ 
    class Router router;
    std::function<std::string(Payload)> handler
        = router.getPathHandler(path);
    if (!handler)
        return generateHTTPResponse(httpVersion, getNotFoundCode(), getContentType());
    return generateHTTPResponse(httpVersion, getOKCode(), getContentType(), handler(payload));
}
