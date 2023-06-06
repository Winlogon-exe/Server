#include <iostream>
#include<thread>
#include"Client.h"
#include"Server.h"


int main() {
    setlocale(LC_ALL, "RUS");
    boost::asio::io_context io_context;
    boost::asio::io_context io_context2;

    //ussualy ports should  be differens  but if build on 1 PC ,need to use 1 port
    uint16_t port_server = 8080;

    // ������� Server � �������� io_context � port � �����������
    boost::asio::streambuf buffer_server;
    auto server = std::make_shared<Server>(io_context, port_server, buffer_server);

    // ������� Client � �������� io_context � port � �����������
    auto client = std::make_shared<Client>(io_context2, port_server, buffer_server);
    server->Listening();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    client->ConnectToServer();

    // ��������� io_context 
    std::thread server_thread([&]() { io_context.run(); });

    std::thread client_thread([&]() {io_context2.run(); });

    server_thread.join();
    client_thread.join();
    
    return 0;
}