#include "system.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string System::ExecuteCommand(const char* command) {
    std::array<char, 256> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string System::EthPortIP() {
    std::string eth0_data = "";
    try
    {
        eth0_data = System::ExecuteCommand("ifconfig eth0");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if (eth0_data.empty())
        throw std::runtime_error("Could not find eth0, connecting to localhost..\n");

    eth0_data = eth0_data.substr(
        eth0_data.find("broadcast") + std::string("broadcast").length() + 1
    );
    return eth0_data.substr(0, eth0_data.find("\n"));
}

System::CommandLineParameters System::GetCmdLineParameters(int argc, char *argv[]) {
    System::CommandLineParameters cmd_params;

    for (int it = 0; it < argc; it++) {
        cmd_params.parameters.push_back(argv[it]);
    }

    return cmd_params;
}

Endpoint System::GetEndpointToBind(CommandLineParameters cmd_params) {
    std::string ip = "127.0.0.1";
    uint16_t port;
    try
    {
        ip = System::EthPortIP();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        port = cmd_params.parameters.size() >= 2 ? std::stoi(cmd_params.parameters[1]) : 4000;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw std::invalid_argument("Invalid arguments!");
    }
    return Endpoint(ip, port);
}
