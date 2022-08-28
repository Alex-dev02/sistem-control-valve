#include "system.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>

std::string System::ExecuteCommand(const char* command) {
    //checking if the command is valid
    std::string str_command = command;
    if (str_command.find(" ") != str_command.length() && !ValidCommand(str_command.substr(0, str_command.find(" "))))
        throw std::invalid_argument("Access denied for executing: " + str_command.substr(0, str_command.find(" ")));
    if (str_command.find(" ") == str_command.length() && !ValidCommand(str_command))
        throw std::invalid_argument("Access denied for executing " + str_command.substr(0, str_command.find(" ")));

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

std::string System::InterfaceIP(std::string interface) {
    std::string interface_data = "";
    if (interface == "lo")
        return "127.0.0.1";
    try
    {
        std::string ip = System::ExecuteCommand(std::string("ifconfig " + interface + " | grep 'inet '| cut -d: -f2 | awk '{print $2}'").c_str());
        if (ip.empty())
            throw std::runtime_error("Could not find " + interface + ", connecting to localhost...\n");

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return "127.0.0.1";
}

System::CommandLineParameters System::GetCmdLineParameters(int argc, char *argv[]) {
    System::CommandLineParameters cmd_params;

    for (int it = 0; it < argc; it++) {
        cmd_params.parameters.push_back(argv[it]);
    }

    return cmd_params;
}

Endpoint System::GetEndpointToBind(CommandLineParameters cmd_params) {
    std::string ip = "127.0.0.1"; // default
    uint16_t port = 4000; // default

    std::vector<std::string>::iterator interface_pos =
        std::find(cmd_params.parameters.begin(), cmd_params.parameters.end(), "-i");
    if (interface_pos != cmd_params.parameters.end() && cmd_params.parameters.size() >= interface_pos - cmd_params.parameters.begin()) {
        try
        {
            ip = InterfaceIP(*(interface_pos + 1));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::vector<std::string>::iterator port_pos = 
        std::find(cmd_params.parameters.begin(), cmd_params.parameters.end(), "-port");
    if (port_pos != cmd_params.parameters.end() && cmd_params.parameters.size() >= port_pos - cmd_params.parameters.begin()) {
        try
        {
            port = std::stoi(*(port_pos + 1));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw std::invalid_argument("Invalid parameters passed to the executable!");
        }
    }
    return Endpoint(ip, port);
}

bool System::ValidCommand(std::string command) {
    return
        std::find(m_valid_commands.begin(), m_valid_commands.end(), command) != m_valid_commands.end();
}

const std::vector<std::string> System::m_valid_commands = {"ifconfig", "cat", "pwd"};
