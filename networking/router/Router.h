#include <unordered_map>
#include <functional>

// The route handler should return a string, representing the data
// returned by the handler
// The input string should be either the payload for a POST function
// Or the variables transmited through the path with GET/PUT
// ex: /myPath/temp?new=15 -> std::string("new=15");

class Router {
    static std::unordered_map<std::string, std::function<std::string(std::string)>> routes;
public:
    Router();
    static void addPath(std::string &path, std::function<std::string(std::string)>);
    std::function<std::string(std::string)> getPathHandler(std::string &path);
};