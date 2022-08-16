#pragma once

#include "http.hpp"
#include "response.hpp"

class HTTP {
public:
    HTTP();
    Response CreateResponse(Utils::HTTPResponseCode response_code, std::string content = "") const;

    std::string GetVersion() const;
private:
    std::string m_version = "1.1";
};
