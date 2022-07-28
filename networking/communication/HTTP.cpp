#include "HTTP.hpp"

HTTP::HTTP()
{}

Response HTTP::CreateResponse(Utils::HTTPResponseCode response_code, std::string content) {
    return Response(
        "HTTP/" + m_version + ' ' + Utils::ResponseCodeToString(response_code) + '\n' +
        "Content-Length: " + std::to_string(content.length()) + '\n' + "Content-Type: text/plain"
        + "\n\n" + content,
        Utils::Protocol::HTTP
    );
}
