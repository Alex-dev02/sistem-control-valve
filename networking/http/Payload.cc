#include "Payload.h"

void Payload::add_path_vars(std::string http_response) {
    int pos_start_vars = 0;
    for (int i = 0; i < http_response.length(); i++) {
        if (http_response[i] == '?') {
            pos_start_vars = i + 1;
            break;
        }
    }
    std::string var_name, var_value;
    bool getting_var_name = true;

    for (int it = pos_start_vars; it < http_response.length(); it++) {
        if (http_response[it] == '&' ) {
            getting_var_name = true;
            path_vars.emplace(var_name, var_value);
            var_name = "";
            var_value = "";
            continue;
        }
        if (http_response[it] == '=') {
            getting_var_name = false;
            continue;
        }
        if (getting_var_name)
            var_name.push_back(http_response[it]);
        else
            var_value.push_back(http_response[it]);

        if (http_response[it] == ' ') {
            path_vars.emplace(var_name, var_value);
            break;
        }
    }
}

Payload::Payload(std::string http_response) {
    // here we will extract the data from the raw http response
    add_path_vars(http_response);
}

std::string Payload::get_path_var(std::string var_name) {
    auto var = path_vars.find(var_name);
    return var != path_vars.end() ? var->second : nullptr;
}
