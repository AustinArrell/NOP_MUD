
#include "game_state.hpp"
#include <iostream>

game_state::game_state(sf::Font& f, sf::RenderWindow& w):
    font {f},
    input_f(f, w),
    mouse_pos { 0 , 0 },
    window {w}
{
    input_f.set_pos(0,w.getSize().y - input_f.get_char_size() - 4); // 4 for padding
}

void game_state::handle_events(const sf::Event& e)
{
    if (e.type == sf::Event::TextEntered)
    {   
        //if backspace is pressed pop off the buffer
        if(e.key.code == 8)
        {
            input_f.pop_buffer();
        }
        else if(e.key.code >= 0 && e.key.code <= 127 && std::isprint(e.key.code))
        {
            input_f.push_buffer(static_cast<char>(e.key.code));
        }
                
    }
    if (e.type == sf::Event::KeyPressed)
    {
        if(e.key.control && e.key.code == sf::Keyboard::V)
        {
            input_f.push_buffer(sf::Clipboard::getString());
        }
        if (e.key.code == sf::Keyboard::Left)
        {
            input_f.set_cursor_offset(1);
        }
        if (e.key.code == sf::Keyboard::Right)
        {
            input_f.set_cursor_offset(-1);
        }
        if (e.key.code == sf::Keyboard::Home)
        {
            input_f.send_cursor_home();
        }
        if (e.key.code == sf::Keyboard::End)
        {
            input_f.send_cursor_end();
        }
    }
    if(e.type == sf::Event::MouseMoved)
    {
        mouse_pos = sf::Mouse::getPosition(window);
        std::cout << "Mouse Pos: " << mouse_pos.x << " , " << mouse_pos.y << "\n";
    }
    if(e.type == sf::Event::MouseButtonPressed)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            input_f.set_cursor_offset(mouse_pos);
        }
    }
}

    
void game_state::update()
{
    input_f.update();
}

void game_state::draw()const
{
    input_f.draw();
}

void game_state::cleanup()
{

}

void game_state::startup()
{

}