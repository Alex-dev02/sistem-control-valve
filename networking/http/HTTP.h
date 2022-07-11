#include <functional>

class HTTP {
public:
    HTTP(std::string version = "HTTP/1.1");
    std::string generateHTTPResponse(std::string &path, std::function<std::string(std::string)>);
};