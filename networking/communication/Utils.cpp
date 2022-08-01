#include "Utils.hpp"

namespace Utils {

std::string ResponseCodeToString(int response_code) {
    switch (response_code)
    {
        case 200 ... 299 : return std::to_string(response_code) + " OK";
        case 401 : return std::to_string(response_code) +  " Not Authorized";
        case 404 : return std::to_string(response_code) +  " Not Found"; 
        case 500 ... 509 : return std::to_string(response_code) +  " Server Error";
    }
    switch (response_code)
    {
        case 0 : return std::to_string(response_code) + " Server Error";
        case 1 : return std::to_string(response_code) + " OK";
        case 2 : return std::to_string(response_code) + " Not Found";
        case 3 : return std::to_string(response_code) + " Not Authorized";
    }
    return "404 Not Found";
}

HTTPResponseCode HTTPResponseCodeToEnum(int response_code) {
    switch (response_code)
    {
        case 200 ... 299: return HTTPResponseCode::H_OK;
        case 401 : return HTTPResponseCode::H_NotAuth;
        case 404 : return HTTPResponseCode::H_NotFound; 
        case 500 ... 599: return HTTPResponseCode::H_ServErr;
    }
    return HTTPResponseCode::H_NotFound;
}

IotDCPResponseCode IotDCPResponseCodeToEnum(int response_code) {
    switch (response_code) {
        case 0 : return I_ServErr;
        case 1 : return I_OK;
        case 2 : return I_NotFound;
        case 3 : return I_NotAuth;
    }
    return I_NotFound;
}

}
