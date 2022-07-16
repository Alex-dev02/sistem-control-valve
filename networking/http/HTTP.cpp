#include "HTTP.hpp"
#include "Payload.hpp"

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

std::string HTTP::getPath(std::string http_req) {
    std::string path;
    bool pathB = false;
    for (int it = 0; it < http_req.length(); it++) {
        if (pathB == true)
            path.push_back(http_req[it]);

        if ((http_req[it] == ' ' || http_req[it] == '?') && pathB ) {
            path.pop_back();
            break;
        }

        if (http_req[it] == ' ') {
            pathB = true;
        }
    }
    return path;
}

bool HTTP::successResponse(std::string http_res) {
    if (http_res.find("20") != std::string::npos)
        return true;
    return false;
}

std::string HTTP::getHTTPResponse(std::string http_req, Router router, std::string httpVersion){ 
    std::string path = getPath(http_req);
    std::function<std::string(Payload)> handler
        = router.getPathHandler(path);
    if (!handler)
        return generateHTTPResponse(httpVersion, getNotFoundCode(), getContentType());
    return generateHTTPResponse(httpVersion, getOKCode(), getContentType(), handler(Payload(http_req)));
}
