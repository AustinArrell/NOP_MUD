
#include <SFML/Graphics.hpp>
#include <iostream>

#include "input_field.hpp"
#include "game_state.hpp"
#include "login_state.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 720), "NOP MUD");
    window.setVerticalSyncEnabled(true);
  
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