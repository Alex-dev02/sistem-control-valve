#include "Router.hpp"
#include "../communication/Utils.hpp"
#include "../communication/IotDCP.hpp"
#include "../communication/HTTP.hpp"

#include <iostream>

Router::Router() {}

bool Router::AddPath(std::string path, std::function<Response(Request)> handler) {
    try {
        m_routes.emplace(path, handler);
        return m_routes.find(path) != m_routes.end();      
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return false;
    }
}

Response Router::GetResponse(Request request) {
    auto handler = m_routes.find(request.GetPath());
    if (handler != m_routes.end())
        return (handler->second)(request);
    if (request.GetProtocol() == Utils::Protocol::IotDCP) {
        IotDCP dcp;
        return dcp.CreateResponse(Utils::IotDCPResponseCode::I_NotFound);
    }
    HTTP http;
    return http.CreateResponse(Utils::HTTPResponseCode::H_NotFound, "Not a valid path");
}
