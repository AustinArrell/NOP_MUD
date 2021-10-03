#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>

#include "input_field.hpp"
#include "game_state.hpp"
#include "login_state.hpp"
#include "network.hpp"

int main()
{
    // std::string server_ip;
    // std::cout << "Server IP : ";
    // std::getline(std::cin, server_ip);
    // std::cout << std::endl;

    // std::string username;
    // std::cout << "User Name : ";
    // std::getline(std::cin, username);
    // std::cout << std::endl;

    // sf::TcpSocket socket;
    // sf::Socket::Status status = socket.connect(server_ip, 53000);
    // if (status != sf::Socket::Done)
    // {
    //     std::cout << "Failed to connect to server!\n";
    //     system("pause");
    //     return -1;
    // }

    // session_id id;
    // mud_packet packet;

    // packet.receive(socket);
    // id = packet.id;

    // packet.type = packet_type::username;
    // packet.data = username;

    // packet.send(socket);

    // std::cout
    //     << "Connected to Server : "
    //     << socket.getRemoteAddress()
    //     << ":"
    //     << socket.getRemotePort()
    //     << std::endl;
    // std::cout << "Session id : " << id << std::endl;


    // while(true)
    // {
    //     std::cout << " > ";
    //     std::getline(std::cin, packet.data);

    //     packet.type = packet_type::command;
    //     packet.id = id;

    //     packet.send(socket);
    // }


    sf::RenderWindow window(sf::VideoMode(960, 720), "NOP MUD");

    sf::Font font;
    font.loadFromFile("../resources/fonts/Roboto-Regular.ttf");

    game_state game(font, window);
    login_state login(font, window);

    add_state("game" , game);
    add_state("login" , login);

    change_state("login");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            handle_events(event);
        }

        window.clear();

        update_state();

        render_state();

        window.display();
    }

    return 0;
}