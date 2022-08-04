#pragma once

#include <string>

namespace Utils{
    enum RequestType {GET, PUT};
    enum HTTPResponseCode {H_ServErr = 500, H_OK = 200, H_NotFound = 404, H_NotAuth = 401};
    enum IotDCPResponseCode {I_ServErr = 0, I_OK = 1, I_NotFound = 2, I_NotAuth = 3};
    enum Protocol {IotDCP, HTTP};

    std::string ResponseCodeToString(int response_code);
    HTTPResponseCode HTTPResponseCodeToEnum(int response_code);
    IotDCPResponseCode IotDCPResponseCodeToEnum(int response_code);
}