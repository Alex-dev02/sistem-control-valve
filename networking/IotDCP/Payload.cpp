#include "Payload.hpp"

void Payload::AddPathVars() {
    int pos_start_vars = 0;
    for (int i = 0; i < m_raw_http_req.length(); i++) {
        if (m_raw_http_req[i] == '?') {
            pos_start_vars = i + 1;
            break;
        }
    }
    std::string var_name, var_value;
    bool getting_var_name = true;

    for (int it = pos_start_vars; it < m_raw_http_req.length(); it++) {
        if (m_raw_http_req[it] == '&' ) {
            getting_var_name = true;
           m_path_vars.emplace(var_name, var_value);
            var_name = "";
            var_value = "";
            continue;
        }
        if (m_raw_http_req[it] == '=') {
            getting_var_name = false;
            continue;
        }
        if (getting_var_name)
            var_name.push_back(m_raw_http_req[it]);
        else
            var_value.push_back(m_raw_http_req[it]);

        if (m_raw_http_req[it] == ' ') {
           m_path_vars.emplace(var_name, var_value);
            break;
        }
    }
}

Payload::Payload(std::string http_req) {
    m_raw_http_req = http_req;
    // here we will extract the data from the raw http response
    AddPathVars();
}

std::string Payload::GetRawRequest() {
    return m_raw_http_req;
}


std::string Payload::GetPathVar(std::string var_name) {
    auto var = m_path_vars.find(var_name);
    return var != m_path_vars.end() ? var->second : nullptr;
}
