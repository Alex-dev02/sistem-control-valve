#pragma once

#include <string>

class Response{
public:
    enum HttpResponseCode {HttpOK = 200, HttpNotAuth = 401, HttpNotFound = 404, HttpServErr = 500};
    enum IotDCPResponseCode {IoTServErr = 0, IoTOK = 1, IoTNotFound = 2, IoTNotAuth = 3};
    
    
    Response(Response::HttpResponseCode code, std::string content = "");
    Response(Response::IotDCPResponseCode code, std::string content = "");
    std::string GetRawHttpResponse();
    std::string GetRawIotDCPResponse();
private:
    std::string m_content;
    int m_response_code;

    std::string ResponseCodeToWords();
};
