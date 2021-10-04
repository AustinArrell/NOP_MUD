#include "server.hpp"

#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <string>
#include <unordered_map>

namespace
{
    sf::TcpListener listener;

    // socket buffer
    std::array<sf::TcpSocket,max_clients> sockets;
    session_id next_socket {0u};

    std::vector<session_id> active_sockets;
    std::vector<session_id> available_sockets;
    std::vector<session_id> drop_queue;

    std::unordered_map<session_id,std::string> usernames;

    sf::SocketSelector selector;

    // for multi threaded logging
    std::mutex console_mutex;
}

// -- helpers
void queue_drop(session_id id);
void drop_queued();


//**********************************************************************
void run_server()
{
    if(!init_server())
    { return; }

    while(true)
    {
        if(selector.wait())
        {
            // new connections
            if(selector.isReady(listener))
            {
                add_client();
            }

            // existing connections
            for(auto id : active_sockets)
            {
                sf::TcpSocket& client { sockets[id] };
                if(selector.isReady(client))
                {
                    recieve_from_client(id);
                }
            }

            // we can't remove clients from 'active_sockets' while iterating so we queue them
            // the drap them after iterating (queue_drop() is called form recieve_from_client())
            drop_queued();
        }
    }
}


//**********************************************************************
void log(const std::string& msg)
{
    std::scoped_lock lock {console_mutex};
    std::cout << msg << std::endl;
}


//**********************************************************************
bool init_server()
{
    if(listener.listen(port) != sf::Socket::Done)
    {
        return false;
    }

    selector.add(listener);

    log("Listening for connections on port " + std::to_string(port));

    return true;
}


//**********************************************************************
bool recieve_from_client(session_id id)
{
    sf::TcpSocket& client { sockets[id] };

    mud_packet packet;

    auto status = packet.receive(client);

    if(status == sf::Socket::Done)
    {
        if(id != packet.id)
        {
            // Maybe kick client here?
            log("Connection Error!");
            return false;
        }

        switch(packet.type)
        {
            case packet_type::command:
                log(usernames[id] + " : " + packet.data);

                { // temp
                    mud_packet sendpacket;
                    sendpacket.id = max_clients;
                    sendpacket.type = packet_type::server_response;
                    sendpacket.data = std::to_string( packet.data.size() );
                    sendpacket.send(client);

                    // send data to all other clients
                    for(auto toid : active_sockets)
                    {
                        if(std::find(drop_queue.begin(), drop_queue.end(), toid) != drop_queue.end())
                        { continue; }

                        if(toid == id)
                        { continue; }

                        sf::TcpSocket& toclient { sockets[toid] };

                        sendpacket.type = packet_type::server_message;
                        sendpacket.data = usernames[id] + ": " + packet.data;

                        sendpacket.send(toclient);
                    }
                }

                break;

            case packet_type::username:
                usernames[id] = packet.data;
                break;
        }
    }
    else if(status == sf::Socket::Disconnected)
    {
        queue_drop(id);
    }

    return true;
}


//**********************************************************************
session_id get_new_session_id()
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
        return (session_id) max_clients;
    }

    return id;
}


//**********************************************************************
session_id add_client()
{
    session_id id { get_new_session_id() };

    if(id == max_clients)
    { return id; }

    sf::TcpSocket& newclient = sockets[id];

    if(listener.accept(newclient) == sf::Socket::Done)
    {
        mud_packet packet;
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
            newclient.disconnect();
        }
    }
    else
    {
        log("Failed to accept connection!");
        available_sockets.push_back(id);
    }

    return id;
}


//**********************************************************************
void drop_client(session_id id)
{
    sf::TcpSocket& client { sockets[id] };

    selector.remove(client);

    std::erase(active_sockets, id);

    available_sockets.push_back(id);

    log("Client disconnected : " + usernames[id]);
}


//**********************************************************************
void queue_drop(session_id id)
{
    drop_queue.push_back(id);
}


//**********************************************************************
void drop_queued()
{
    for(auto id : drop_queue)
    {
        drop_client(id);
    }

    drop_queue.clear();
}