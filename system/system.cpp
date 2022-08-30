#include "system.hpp"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>

std::unordered_map<std::string, std::string> System::CommandLineParameters::parameters = {};

void System::InitParams(int argc, char *argv[]) {
    System::CommandLineParameters::parameters = GetCmdLineParameters(argc, argv);
}

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
        std::string ip_inet_addr = System::ExecuteCommand(std::string("ifconfig " + interface + " | grep 'inet addr'| cut -d: -f2 | awk '{print $2}'").c_str());
        if (!ip_inet_addr.empty())
            return ip_inet_addr;
        std::string ip_inet = System::ExecuteCommand(std::string("ifconfig " + interface + " | grep 'inet '| cut -d: -f2 | awk '{print $2}'").c_str());
        if (ip_inet.empty())
            throw std::runtime_error("Could not find " + interface + ", connecting to localhost...\n");
        return ip_inet;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return "127.0.0.1";
}

std::string System::GetConfigPath() {
    auto config_path = System::CommandLineParameters::parameters.find("-conf");
    if (config_path == System::CommandLineParameters::parameters.end())
        throw std::runtime_error("No configuration path provided!");
    return config_path->second;
}

std::unordered_map<std::string, std::string> System::GetCmdLineParameters(int argc, char *argv[]) {
    std::unordered_map<std::string, std::string> cmd_params;

    for (int it = 1; it < argc - 1; it++) {
        cmd_params.emplace(argv[it], argv[it+1]);
    }

    return cmd_params;
}

Endpoint System::GetEndpointToBind() {
    std::string ip = "127.0.0.1"; // default
    uint16_t port = 4000; // default

    auto interface = System::CommandLineParameters::parameters.find("-i");
    if (interface != System::CommandLineParameters::parameters.end()) {
        try
        {
            ip = InterfaceIP(interface->second);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    auto param_port = System::CommandLineParameters::parameters.find("-port");
    if (param_port != System::CommandLineParameters::parameters.end()) {
        try
        {
            port = std::stoi(param_port->second);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw std::invalid_argument("Invalid parameters passed to the executable!");
        }
    }
    return Endpoint(ip, port);
}

bool System::FileExists(std::string file_name) {
    std::ifstream fin(file_name);
    return fin.good();
}

bool System::CreateFile(std::string file_name, std::string contet) {
    std::ofstream fout(file_name);
    fout << contet;
    return !fout;
}

bool System::ValidCommand(std::string command) {
    return
        std::find(m_valid_commands.begin(), m_valid_commands.end(), command) != m_valid_commands.end();
}

const std::vector<std::string> System::m_valid_commands = {"ifconfig", "cat", "pwd"};
