#pragma once

#include <string>

#include "Payload.h"

class HTTP {
    static std::string getNotFoundCode();
    static std::string getOKCode();
    static std::string getContentType(std::string type = "text/plain");
    static std::string generateHTTPResponse(
        std::string httpVersion,
        std::string responseCode,
        std::string contentType,
        std::string content = ""
    );
public:
    static std::string getHTTPResponse(std::string &path, Payload http_response, std::string httpVersion = "HTTP/1.1");
};