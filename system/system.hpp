#pragma once

#include <string>
#include <vector>
#include <networking/endpoint.hpp>

class System {
public:
    static std::string ExecuteCommand(const char* command);
    static std::string EthPortIP();

    struct CommandLineParameters {
        std::vector<std::string> parameters;
    };
    static CommandLineParameters GetCmdLineParameters(int argc, char *argv[]);
    static Endpoint GetEndpointToBind(CommandLineParameters cmd_params);
};
