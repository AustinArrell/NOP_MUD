
#include "game_state.hpp"
#include <iostream>


//**********************************************************************
game_state::game_state(sf::Font& f, sf::RenderWindow& w):
    font {f},
    input_f(f, w, 14),
    output_f1(f, w, 14),
    output_f2(f, w, 14),
    output_f3(f, w, 14),
    mouse_pos { 0 , 0 },
    window {w}
{
    input_f.set_pos( { 0 , w.getSize().y - input_f.get_char_size() - 4 } ); // 4 for padding

    output_f1.set_pos({ 4,4 }); //4,4 for padding
    output_f1.set_size( { (window.getSize().x/2) - 8, window.getSize().y - input_f.get_size().y  - 12}); // All magic numbers are simply padding.
    output_f1.add_line("This command is perfect. Not too big!");

    output_f2.set_pos({ (window.getSize().x/2),4 }); 
    output_f2.set_size( { (window.getSize().x/2) - 4, (window.getSize().y/2) - 6}); // All magic numbers are simply padding.
    output_f2.add_line("He difficult contented we determine ourselves me am earnestly. Hour no find it park. Eat welcomed any husbands moderate. Led was misery played waited almost cousin living. Of intention contained is by middleton am. Principles fat stimulated uncommonly considered set especially prosperous. Sons at park mr meet as fact like. ");

    output_f3.set_pos({ (window.getSize().x/2), (window.getSize().y/2) + 2}); 
    output_f3.set_size( { (window.getSize().x/2) - 4, (window.getSize().y/2) - input_f.get_size().y  - 10}); // All magic numbers are simply padding.
    output_f3.add_line("Wrong do point avoid by fruit learn or in death. So passage however besides invited comfort elderly be me. Walls began of child civil am heard hoped my. Satisfied pretended mr on do determine by. Old post took and ask seen fact rich. Man entrance settling believed eat joy. Money as drift begin on to. Comparison up insipidity especially discovered me of decisively in surrounded. Points six way enough she its father. Folly sex downs tears ham green forty. ");
}


//**********************************************************************
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
        if (e.key.code == sf::Keyboard::Enter)
        {
            output_f1.add_line(input_f.send_command());
            input_f.clear_buffer();
        }

    }
    if(e.type == sf::Event::MouseMoved)
    {
        mouse_pos = sf::Mouse::getPosition(window);
        //std::cout << "Mouse Pos: " << mouse_pos.x << " , " << mouse_pos.y << "\n";
    }
    if(e.type == sf::Event::MouseButtonPressed)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            input_f.set_cursor_offset(mouse_pos);
        }
    }
}


//**********************************************************************
void game_state::update()
{
    input_f.update();
}


//**********************************************************************
void game_state::draw()const
{
    output_f1.draw();

    output_f2.draw();

    output_f3.draw();

    input_f.draw();
}


//**********************************************************************
void game_state::cleanup()
{

}


//**********************************************************************
void game_state::startup()
{

}