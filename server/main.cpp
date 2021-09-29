#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <string>
#include <unordered_map>

#include <SFML/Network.hpp>

#include "network.hpp"

namespace
{

    sf::TcpListener listener;

    // socket buffer
    std::array<sf::TcpSocket,max_clients> sockets;
    session_id next_socket {0u};

    std::vector<session_id> active_sockets;
    std::vector<session_id> available_sockets;

    std::unordered_map<session_id,std::string> usernames;

    sf::SocketSelector selector;

    // for multi threaded logging
    std::mutex console_mutex;
}


void log(const std::string& msg)
{
    std::scoped_lock lock {console_mutex};
    std::cout << msg << std::endl;
}


int main()
{
    // Network cycle
    {
        if(listener.listen(port) != sf::Socket::Done)
        {
            log("Failed to bind port!");
            system("pause");
            std::abort();
            return -1;
        }

        selector.add(listener);

        log("Listening for connections on port " + std::to_string(port));

        mud_packet packet;

        while(true)
        {
            if(selector.wait())
            {
                // sf::SocketSelector can't tell us wich client socket is recieving data
                // so we must check all of them

                for(auto it {active_sockets.begin()}; it != active_sockets.end();)
                {
                    session_id id = *it;
                    sf::TcpSocket& client { sockets[id] };

                    if(selector.isReady(client))
                    {
                        auto status = packet.receive(client);

                        if(status == sf::Socket::Done)
                        {
                            if(id != packet.id)
                            {
                                // Maybe kick client here?
                                log("Connection Error!");
                                continue;
                            }

                            switch(packet.type)
                            {
                                case packet_type::command:
                                    log(usernames[id] + " : " + packet.data);
                                    break;

                                case packet_type::username:
                                    usernames[id] = packet.data;
                                    break;
                            }

                            ++it;
                        }
                        else if(status == sf::Socket::Disconnected)
                        {
                            log("Client disconnected : " + usernames[id]);

                            selector.remove(client);
                            it = active_sockets.erase(it);
                            available_sockets.push_back(id);
                        }
                    }
                    else
                    {
                        ++it;
                    }
                }

                // -- check for new connections

                if(selector.isReady(listener))
                {
                    session_id id;

                    if(!available_sockets.empty())
                    {
                        id = available_sockets.back();
                        available_sockets.pop_back();
                    }
                    else if (next_socket < max_clients)
                    {
                        id = next_socket;
                        ++next_socket;
                    }
                    else
                    {
                        log(" !!!! Max clients reached !!!! ");
                        continue;
                    }

                    sf::TcpSocket& newclient = sockets[id];

                    if(listener.accept(newclient) == sf::Socket::Done)
                    {
                        packet.type = packet_type::session_id;
                        packet.id   = id;
                        packet.data = "";

                        packet.send(newclient);

                        packet.receive(newclient);

                        if(id == packet.id && packet.type == packet_type::username)
                        {
                            selector.add(newclient);
                            active_sockets.push_back(id);
                            usernames[id] = packet.data;
                            log("Client connected : " + packet.data);
                        }
                        else
                        {
                            log("Connection rejected");
                            available_sockets.push_back(id);
                        }
                    }
                    else
                    {
                        log("Failed to accept connection!");
                        available_sockets.push_back(id);
                    }
                }
            }
        }

    }
    system("pause");


    return 0;
}