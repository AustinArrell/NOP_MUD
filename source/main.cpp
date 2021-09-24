#include <SFML/Graphics.hpp>
#include <iostream>

#include "input_field.hpp"
#include "game_state.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 720), "NOP MUD");

    sf::Font font;
    font.loadFromFile("../resources/fonts/Roboto-Regular.ttf");

    game_state game(font, window);
    add_state("game" , game);
    change_state("game");
    
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