#include <iostream>
#include <thread>
#include <chrono>

#include "Valve.hpp"
#include "../../networking/socket/TcpClient.hpp"
#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/socket/NetworkStream.hpp"
#include "../../networking/router/Router.hpp"

void DisplayTemperature(Valve &valve) {
    while (true) {
        std::cout << "Current Target: " << valve.GetCurrentTarget() << '\n';
        std::cout << "Temperature: " << valve.GetTemperature() << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main(int argc, char *argv[]) {
    Valve valve;
    
    auto DisplayTempThread = std::thread(DisplayTemperature, std::ref(valve));
    DisplayTempThread.detach();

    TcpListener server(
        argc >= 2 ? argv[1] : "127.0.0.1",
        argc >= 3 ? argv[2] : "5000"
    );
    server.Start();
    Router router = valve.GetRouter();
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        std::string res = router.GetPathHandlerResponse(req);
        stream.Write(res);
        stream.Close();
    }
}