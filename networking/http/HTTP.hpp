#pragma once

#include <string>

class HTTP {
    static bool request_or_response();
    static std::string getNotFoundCode();
    static std::string getOKCode();
    static std::string getContentType(std::string type = "text/plain");
    static std::string generateHTTPResponse(
        std::string httpVersion,
        std::string responseCode,
        std::string contentType,
        std::string content = ""
    );
    static std::string getPath(std::string http_req);
public:
    static bool successResponse(std::string http_res);
    static std::string getHTTPResponse(std::string http_req, std::string httpVersion = "HTTP/1.1");
};