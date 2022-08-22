#pragma once

#include "response.hpp"
#include "endpoint.hpp"
#include "tcp_client.hpp"
#include "tcp_listener.hpp"
#include "request.hpp"

template <typename T>
class Server {
public:
    Server() {}
    void Listen(const Endpoint& endpoint) {
        T router(endpoint);
        TcpListener listener(endpoint.GetIPAddress(), endpoint.GetPort());
        listener.Start();
        while (true) {
            std::cout << "Waiting for a new connection...\n";
            TcpClient client = listener.AcceptTcpClient();
            NetworkStream stream = client.GetStream();
            std::string req = stream.Read();
            Response res = router.GetResponse(Request(req)); 
            try
            {
                stream.Write(res.GetRawResponse());
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            stream.Close();
        }
    }
};
