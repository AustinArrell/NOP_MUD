
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
    //output_f1.add_line("", false);

    output_f2.set_pos({ (window.getSize().x/2),4 }); 
    output_f2.set_size( { (window.getSize().x/2) - 4, (window.getSize().y/2) - 6}); // All magic numbers are simply padding.
    //output_f2.add_line("", false);

    output_f3.set_pos({ (window.getSize().x/2), (window.getSize().y/2) + 2}); 
    output_f3.set_size( { (window.getSize().x/2) - 4, (window.getSize().y/2) - input_f.get_size().y  - 10}); // All magic numbers are simply padding.
    output_f3.add_line("To replace programmers with robots, clients will have to accurately describe what they want. We're safe.");
    output_f3.add_line("------" , false);
    output_f3.add_line("The human brain is amazing. It functions 24/7 from the day we're born and only stops when trying to write code or speaking to someone attractive");
    output_f3.add_line("------" , false);
    output_f3.add_line("Pick a password: (Don't reuse your bank password we store everything in the clear)");
    output_f3.add_line("------" , false);
    output_f3.add_line("Never spend 6 minutes doing something by hand when you can spend 6 hours failing to automate it.");
    output_f3.add_line("------" , false);
    output_f3.add_line("You peel the carrot. You chop the carrot. You put the carrot in the stew. There are whole carrots in your stew. Your peeler is several versions behind and they added support for chopped carrots in version 4.8");
    output_f3.add_line("------" , false);
    output_f3.add_line("Give a man a program, frustrate him for a day. Teach a man to program, frustrate him for a lifetime");
    output_f3.add_line("------" , false);
    output_f3.add_line("REMINDER: A few hours of trial and error can save you several minutes of looking at the documentation");
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
            output_f2.add_line(input_f.send_command());

            output_f2.add_line("------" , false);

            output_f1.add_line("Command Output example. This text can be as long as you want it to be. We can just keep on going. Perhaps this is a room description. Perhaps it is something else. If only I had Douglas' command parser. Imagine the possibilities. Imagine what we may achieve.");

            output_f1.add_line("------" , false);

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