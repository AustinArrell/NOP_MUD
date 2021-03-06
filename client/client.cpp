#include "client.hpp"
#include "network.hpp"

#include <iostream>

namespace
{
    sf::SocketSelector selector;
    sf::TcpSocket socket;
    session_id id;
    mud_packet packet;
}


//**********************************************************************
bool connect_to_server(const std::string& ip, const std::string& user)
{
    sf::Socket::Status status = socket.connect(ip, port);

    if (status != sf::Socket::Done)
    {
        std::cout << "Failed to connect to server!\n";
        return false;
    }

    packet.receive(socket);

    if(packet.type != packet_type::session_id)
    {
        socket.disconnect();
        std::cout << "Failed to connect to server!\n";
        return false;
    }

    id = packet.id;

    packet.type = packet_type::username;
    packet.data = user;

    packet.send(socket);

    std::cout
        << "Connected to Server : "
        << socket.getRemoteAddress()
        << ":"
        << socket.getRemotePort()
        << std::endl;
    std::cout << "Session id : " << id << std::endl;

    selector.add(socket);

    return true;
}


//**********************************************************************
void send(const std::string& data, packet_type type)
{
    packet.id = id;
    packet.type = type;
    packet.data = data;

    packet.send(socket);
}


//**********************************************************************
const mud_packet& recieve()
{
    packet.type = packet_type::invalid;
    packet.receive(socket);
    return packet;
}


//**********************************************************************
bool data_to_recieve()
{
    return selector.wait(sf::seconds(0.0001f));
}


//**********************************************************************
void disconnect()
{
    socket.disconnect();
}