#pragma once

#include "Utils.hpp"
#include "Response.hpp"

class HTTP {
public:
    HTTP();
    Response CreateResponse(Utils::HTTPResponseCode response_code, std::string content = "");

    std::string GetVersion();
private:
    std::string m_version = "1.1";
};
