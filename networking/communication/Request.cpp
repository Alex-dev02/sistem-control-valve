#include "Request.hpp"

Request::Request(std::string raw_request):
    m_raw_request(raw_request)
{
    if(raw_request.find("IotDCP") != std::string::npos)
        m_protocol = Utils::Protocol::IotDCP;
    else if (raw_request.find("HTTP") != std::string::npos)
        m_protocol = Utils::Protocol::HTTP;
    // else handle invalid request

    MapVarsFromPath();
}

std::string Request::GetPath() {
    std::string path;
    bool pathB = false;
    for (int it = 0; it < m_raw_request.length(); it++) {
        if (pathB == true)
            path.push_back(m_raw_request[it]);

        if ((m_raw_request[it] == ' ' || m_raw_request[it] == '?') && pathB ) {
            path.pop_back();
            break;
        }

        if (m_raw_request[it] == ' ') {
            pathB = true;
        }
    }
    return path;
}

std::string Request::GetPathVar(std::string var_name) {
    auto var = m_path_vars.find(var_name);
    if (var == m_path_vars.end())
        throw std::invalid_argument("The var_name does not correspond to any variable: " + var_name);
    
    return var != m_path_vars.end() ? var->second : nullptr;
}

std::string Request::GetRawRequest() {
    return m_raw_request;
}

Utils::Protocol Request::GetProtocol() {
    return m_protocol;
}

void Request::MapVarsFromPath() {
    int pos_start_vars = 0;
    for (int i = 0; i < m_raw_request.length(); i++) {
        if (m_raw_request[i] == '?') {
            pos_start_vars = i + 1;
            break;
        }
    }
    if (pos_start_vars == 0)
        return;
    std::string var_name, var_value;
    bool getting_var_name = true;

    for (int it = pos_start_vars; it < m_raw_request.length(); it++) {
        if (m_raw_request[it] == '&' ) {
            getting_var_name = true;
           m_path_vars.emplace(var_name, var_value);
            var_name = "";
            var_value = "";
            continue;
        }
        if (m_raw_request[it] == '=') {
            getting_var_name = false;
            continue;
        }
        if (getting_var_name)
            var_name.push_back(m_raw_request[it]);
        else
            var_value.push_back(m_raw_request[it]);

        if (m_raw_request[it] == ' ') {
            var_value.pop_back();
            m_path_vars.emplace(var_name, var_value);
            break;
        }
    }
}
