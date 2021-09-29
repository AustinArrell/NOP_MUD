#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <string>

#include <SFML/Network.hpp>

namespace
{
    constexpr unsigned short port {53000};
    constexpr std::size_t max_clients {500u};

    sf::TcpListener listener;

    std::array<sf::TcpSocket,max_clients> clients;
    std::array<std::mutex,max_clients> client_mutexes;

    std::size_t next_client_index {0u};

    sf::SocketSelector selector;
    // std::mutex selector_mutex;

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

        // recieve vars
        sf::Packet packet;
        std::string data;

        while(true)
        {
            if(selector.wait())
            {
                // sf::SocketSelector can't tell us wich client socket is recieving data
                // so we must check all of them

                if(selector.isReady(listener))
                {
                    // New Connection!!

                    std::scoped_lock lock {client_mutexes[next_client_index]};

                    sf::TcpSocket& newclient = clients[next_client_index];

                    if(listener.accept(newclient) == sf::Socket::Done)
                    {
                        log("Client connected : " + newclient.getRemoteAddress().toString());
                        ++next_client_index;

                        selector.add(newclient);
                    }
                }

                for(auto& client : clients)
                {
                    if(selector.isReady(client))
                    {
                        packet.clear();
                        data.clear();

                        auto status = client.receive(packet);

                        if(status == sf::Socket::Done)
                        {
                            packet >> data;
                            log(client.getRemoteAddress().toString() + " : " + data);
                        }
                        else if(status == sf::Socket::Disconnected)
                        {
                            log("Client disconnected : " + client.getRemoteAddress().toString());
                            selector.remove(client);
                        }
                    }
                }
            }
        }

    }
    system("pause");


    return 0;
}