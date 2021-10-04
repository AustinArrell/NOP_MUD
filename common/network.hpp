#pragma once

#include <string>
#include <cstdint>

#include <SFML/Network.hpp>


using session_id = unsigned long long;

constexpr unsigned short port {53000};
constexpr std::size_t max_clients {500u};


enum class packet_type : uint8_t
{
    command,
    username,
    session_id,
    connection_query,
    connection_acknowledge,
    connection_drop,
    connection_accept,
    server_response,
    server_message,
    invalid
};


class mud_packet
{
public:

    packet_type type;
    session_id id;
    std::string data;

private:

    sf::Packet packet;

public:

    operator sf::Packet& ();

    sf::Socket::Status send(sf::TcpSocket& socket);
    sf::Socket::Status receive(sf::TcpSocket& socket);

    sf::Packet& get();
};


sf::Packet& operator << (sf::Packet& packet, const mud_packet& data);
sf::Packet& operator >> (sf::Packet& packet, mud_packet& data);