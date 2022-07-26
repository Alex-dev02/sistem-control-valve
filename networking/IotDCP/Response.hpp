#pragma once

#include <string>

#include "IotDCP.hpp"

class Response{
public:
    enum HttpResponseCode {HttpOK = 200, HttpNotAuth = 401, HttpNotFound = 404, HttpServErr = 500};
    
    Response(Response::HttpResponseCode response_code, std::string content = "");
    Response(IotDCP::ResponseCode response_code, std::string content = "");
    std::string GetRawHttpResponse();
    std::string GetRawIotDCPResponse();
private:
    std::string m_content;
    int m_response_code;

    std::string ResponseCodeToWords();
};
