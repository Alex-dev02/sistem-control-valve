#pragma once

#include <string>

namespace HttpResponses{
    std::string OK(std::string content = "");
    std::string NotFound();
    std::string ServerError();
}