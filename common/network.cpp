#include "network.hpp"


//**********************************************************************
sf::Socket::Status mud_packet::send(sf::TcpSocket& socket)
{
    packet.clear();
    packet << *this;
    return socket.send(packet);
}


//**********************************************************************
sf::Socket::Status mud_packet::receive(sf::TcpSocket& socket)
{
    auto status = socket.receive(packet);
    packet >> *this;
    return status;
}


//**********************************************************************
sf::Packet& mud_packet::get()
{
    return packet;
}


//**********************************************************************
sf::Packet& operator << (sf::Packet& packet, const mud_packet& data)
{
    packet << static_cast<uint8_t>(data.type);
    packet << data.id;
    packet << data.data;
    return packet;
}


//**********************************************************************
sf::Packet& operator >> (sf::Packet& packet, mud_packet& data)
{
    uint8_t ty;

    packet >> ty;
    packet >> data.id;
    packet >> data.data;

    data.type = static_cast<packet_type>(ty);

    return packet;
}