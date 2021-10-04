#pragma once

#include "network.hpp"

bool connect_to_server(const std::string& ip, const std::string& user);

void send(const std::string& data, packet_type type);

const mud_packet& recieve();

void disconnect();

bool data_to_recieve();