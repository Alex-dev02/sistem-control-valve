#pragma once

#include <string>

namespace Utils{
    enum RequestType {GET, PUT};
    enum HTTPResponseCode {H_ServErr, H_OK, H_NotFound, H_NotAuth};
    enum IotDCPResponseCode {I_ServErr, I_OK, I_NotFound, I_NotAuth};
    enum Protocol {IotDCP, HTTP};

    std::string ResponseCodeToString(int response_code);
    HTTPResponseCode HTTPResponseCodeToEnum(int response_code);
    IotDCPResponseCode IotDCPResponseCodeToEnum(int response_code);
}