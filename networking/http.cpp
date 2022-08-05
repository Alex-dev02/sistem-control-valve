#include "http.hpp"

#include <iostream>

HTTP::HTTP()
{}

Response HTTP::CreateResponse(Utils::HTTPResponseCode response_code, std::string content) {
    Response res = Response(
        "HTTP/" + m_version + ' ' + Utils::ResponseCodeToString(response_code) + '\n' +
        "Content-Length: " + std::to_string(content.length()) + '\n' + "Content-Type: text/plain"
        + "\n\n" + content
    );
    return res;
}

std::string HTTP::GetVersion() {
    return m_version;
}
