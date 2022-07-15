#include "Payload.hpp"

void Payload::add_path_vars() {
    int pos_start_vars = 0;
    for (int i = 0; i < raw_http_req.length(); i++) {
        if (raw_http_req[i] == '?') {
            pos_start_vars = i + 1;
            break;
        }
    }
    std::string var_name, var_value;
    bool getting_var_name = true;

    for (int it = pos_start_vars; it < raw_http_req.length(); it++) {
        if (raw_http_req[it] == '&' ) {
            getting_var_name = true;
            path_vars.emplace(var_name, var_value);
            var_name = "";
            var_value = "";
            continue;
        }
        if (raw_http_req[it] == '=') {
            getting_var_name = false;
            continue;
        }
        if (getting_var_name)
            var_name.push_back(raw_http_req[it]);
        else
            var_value.push_back(raw_http_req[it]);

        if (raw_http_req[it] == ' ') {
            path_vars.emplace(var_name, var_value);
            break;
        }
    }
}

Payload::Payload(std::string http_req) {
    raw_http_req = http_req;
    // here we will extract the data from the raw http response
    add_path_vars();
}

std::string Payload::get_raw_http_req() {
    return raw_http_req;
}


std::string Payload::get_path_var(std::string var_name) {
    auto var = path_vars.find(var_name);
    return var != path_vars.end() ? var->second : nullptr;
}
