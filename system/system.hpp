#pragma once

#include <string>
#include <vector>
#include <networking/endpoint.hpp>

class System {
public:
    static std::string InterfaceIP(std::string interface);
    static std::string ExecuteCommand(const char* command);
    struct CommandLineParameters {
        std::vector<std::string> parameters;
    };
    static CommandLineParameters GetCmdLineParameters(int argc, char *argv[]);
    static Endpoint GetEndpointToBind(CommandLineParameters cmd_params);
private:
    static bool ValidCommand(std::string command);

    static const std::vector<std::string> m_valid_commands;
};
