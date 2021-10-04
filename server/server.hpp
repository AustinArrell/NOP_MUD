#pragma once

#include "network.hpp"

void log(const std::string& msg);
void run_server();
bool init_server();
bool recieve_from_client(session_id id);
session_id get_new_session_id();
session_id add_client();
void drop_client(session_id id);