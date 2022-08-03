#include "Router.hpp"
#include "../communication/Utils.hpp"
#include "../communication/IotDCP.hpp"

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
    IotDCP dcp;
    std::cout << "\n\n\n" << m_routes.size() << "\n\n\n";
    auto handler = m_routes.find(request.GetPath());
    if (handler != m_routes.end())
        return (handler->second)(request);
    // vezi ca aici trb lucrat mai mult
    return dcp.CreateResponse(Utils::IotDCPResponseCode::I_NotFound);
}
