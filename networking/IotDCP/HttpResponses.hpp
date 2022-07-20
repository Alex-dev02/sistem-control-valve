#pragma once

#include <string>

class HttpResponses{
public:
    std::string OK(std::string content = "");
    std::string NotFound();
    std::string ServerError();

    bool IsResponseASuccess(std::string http_request);
};
