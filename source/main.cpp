#include <SFML/Graphics.hpp>
#include <iostream>

#include "input_field.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "NOP MUD");
    //window.setKeyRepeatEnabled(false);
    sf::Font font;
    
    font.loadFromFile("../resources/fonts/Roboto-Black.ttf");
    
    input_field t(window, font);

    t.set_pos(0,(window.getSize().y) - t.get_char_size() - 5);

    t.set_size(window.getSize().x,window.getSize().y);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::TextEntered)
            {   
                //if backspace is pressed pop off the buffer
                if(event.key.code == 8)
                {
                    t.pop_buffer();
                }
                else if(event.key.code >= 0 && event.key.code <= 127 && std::isprint(event.key.code))
                {
                    t.push_buffer(static_cast<char>(event.key.code));
                }
                
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.control && event.key.code == sf::Keyboard::V)
                {
                    t.push_buffer(sf::Clipboard::getString());
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    t.set_cursor_offset(1);
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    t.set_cursor_offset(-1);
                }
                if (event.key.code == sf::Keyboard::Home)
                {
                    t.send_cursor_home();
                }
                if (event.key.code == sf::Keyboard::End)
                {
                    t.send_cursor_end();
                }
            }
        }

        window.clear();
        t.update();
        t.draw();
        window.display();
    }

    return 0;
}