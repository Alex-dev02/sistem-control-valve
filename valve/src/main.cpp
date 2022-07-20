#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

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

void UpdateTemperature (Valve &valve) {
    std::mutex guard;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        guard.lock();
        valve.IncrementTemperature();
        guard.unlock();
    }
}

int main(int argc, char *argv[]) {
    Valve valve;
    
    auto display_temp_target_thread = std::thread(DisplayTemperature, std::ref(valve));
    display_temp_target_thread.detach();

    auto update_temp_thread = std::thread(UpdateTemperature, std::ref(valve));
    update_temp_thread.detach();

    TcpListener server(
        argc >= 2 ? argv[1] : "5000"
    );
    server.Start();
    Router router = valve.GetRouter();
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        Response res = router.GetResponse(req);
        stream.Write(res.GetRawIotDCPResponse());
        stream.Close();
    }
}
