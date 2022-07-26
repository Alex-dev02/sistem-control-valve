#include "Response.hpp"
#include <iostream>

Response::Response(Response::HttpResponseCode response_code, std::string content):
    m_response_code(response_code),
    m_content(content)
{}

Response::Response(IotDCP::ResponseCode response_code, std::string content):
    m_response_code(response_code),
    m_content(content)
{}

std::string Response::GetRawHttpResponse() {
    std::string res = std::to_string(m_response_code) + ' ' + ResponseCodeToWords()
        + '\n' + "Content-Type: text/plain" + '\n' + "Content-Length: " +
        std::to_string(m_content.length()) + "\n\n" + m_content;  
    return "HTTP/1.1 " + res;
}

std::string Response::GetRawIotDCPResponse() {
    return std::to_string(m_response_code) + ' ' + ResponseCodeToWords() +
    "IotDCP/0.1" + '\n' + "Length " + std::to_string(m_content.length()) +
    m_content;
}

std::string Response::ResponseCodeToWords() {
    switch (m_response_code)
    {
        case 200 : return "OK";
        case 401 : return "Not Authorized";
        case 404 : return "Not Found"; 
        case 500 : return "Server Error";

        case 0 : return "Server Error";
        case 1 : return "OK";
        case 2 : return "Not Fountd";
        case 3 : return "Not Authorized";
    }
    return "OK";
}
