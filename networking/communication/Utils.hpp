#include <string>

namespace Utils{
    enum RequestType {GET, PUT};
    enum ResponseCode {ServErr, OK, NotFound, NotAuth};
    enum Protocol {IotDCP, HTTP};

    std::string ResponseCodeToString();
    ResponseCode ResponseCodeToEnum(int response_code);
}