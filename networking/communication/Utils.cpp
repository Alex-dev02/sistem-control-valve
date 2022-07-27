#include "Utils.hpp"

namespace Utils {

std::string ResponseCodeToString(ResponseCode response_code) {
    switch (response_code)
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

ResponseCode HttpResponseCodeToEnum(int response_code) {
    switch (response_code)
    {
        // HTTP
        case 200 ... 299: return OK;
        case 401 : return NotAuth;
        case 404 : return NotFound; 
        case 500 ... 599: return ServErr;

        // IotDCP
        case 0 : return ServErr;
        case 1 : return OK;
        case 2 : return NotFound;
        case 3 : return NotAuth;
    }
    return NotFound;
}

}
