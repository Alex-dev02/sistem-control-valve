#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <networking/endpoint.hpp>

class System {
public:
    static void InitParams(int argc, char *argv[]);
    static std::string InterfaceIP(std::string interface);
    static std::string ExecuteCommand(const char* command);
    struct CommandLineParameters {
        static std::unordered_map<std::string, std::string> parameters;
    };
    static std::string GetConfigPath();
    static Endpoint GetEndpointToBind();
    static bool FileExists(std::string file_name);
    static bool CreateFile(std::string file_name, std::string content = "");
private:
    static bool ValidCommand(std::string command);
    static std::unordered_map<std::string, std::string> GetCmdLineParameters(int argc, char *argv[]);

    static const std::vector<std::string> m_valid_commands;
};
