#include <unordered_map>
#include <functional>

class Router {
    static std::unordered_map<std::string, std::function<std::string(std::string)>> routes;
public:
    Router();
    static void addPath(std::string &path, std::function<std::string(std::string)>);
    std::function<std::string(std::string)> getPathHandler(std::string &path);
};