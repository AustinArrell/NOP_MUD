
#include "game_state.hpp"
#include "client.hpp"
#include <iostream>
#include <regex>


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
    input_f.set_pos( { 0.0f , w.getSize().y - input_f.get_char_size() - 4.0f } ); // 4 for padding

    output_f1.set_pos({ 4.0f,4.0f }); //4,4 for padding
    output_f1.set_size( { (window.getSize().x/2.0f) - 8.0f, window.getSize().y - input_f.get_size().y  - 12.0f}); // All magic numbers are simply padding.
    //output_f1.add_line("", false);

    output_f2.set_pos({ (window.getSize().x/2.0f),4 });
    output_f2.set_size( { (window.getSize().x/2.0f) - 4.0f, (window.getSize().y/2.0f) - 6.0f}); // All magic numbers are simply padding.
    //output_f2.add_line("", false);

    output_f3.set_pos({ (window.getSize().x/2.0f), (window.getSize().y/2.0f) + 2.0f});
    output_f3.set_size( { (window.getSize().x/2.0f) - 4.0f, (window.getSize().y/2.0f) - input_f.get_size().y  - 10.0f}); // All magic numbers are simply padding.
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
    input_f.handle_events(e);


    if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::Enter)
        {
            send(input_f.get_string(), packet_type::command);

            auto packet = recieve();

            output_f1.add_line(input_f.get_string());
            output_f1.add_line(packet.data , false);
            output_f1.add_line("------" , false);

            input_f.push_history(input_f.get_string());
            
            input_f.clear_buffer();
        }  
}


//**********************************************************************
void game_state::update()
{
    output_f1.update();
  
    output_f2.update();
  
    output_f3.update();

    input_f.update();

    if(data_to_recieve())
    {
        auto packet = recieve();

        if(packet.type == packet_type::server_message)
        {
            output_f1.add_line(packet.data , false);
            output_f1.add_line("------" , false);
        }
    }
}


//**********************************************************************
void game_state::draw() const
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