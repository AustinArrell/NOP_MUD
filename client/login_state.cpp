#include "login_state.hpp"
#include "client.hpp"

#include <iostream>


//**********************************************************************
login_state::login_state(sf::Font& f, sf::RenderWindow& w) :
    font {f},
    window {w},
    address_field  {f,w,16},
    username_field {f,w,16},
    connect_button {w,f,16},
    title          {"Connect to sever", f, 30},
    address_label  {"server address:", f, 16},
    username_label {"username:", f, 16}
{
    float ui_width { 300.0f };
    float ui_height { 30.0f };

    connect_button.set_size({ui_width,ui_height});
    address_field.set_size({ui_width,ui_height});
    username_field.set_size({ui_width,ui_height});

    float x_pad { (window.getSize().x - ui_width) / 2.0f };
    float y_pad { 10.0f };
    float current_y { 100.0f };

    title.setPosition({x_pad, current_y});
    current_y += title.getGlobalBounds().height + y_pad + 50.0f;

    address_label.setPosition({x_pad, current_y});
    current_y += address_label.getGlobalBounds().height + y_pad;

    address_field.set_pos({x_pad, current_y});
    current_y += address_field.get_size().y + y_pad;

    username_label.setPosition({x_pad, current_y});
    current_y += username_label.getGlobalBounds().height + y_pad;

    username_field.set_pos({x_pad, current_y});
    current_y += username_field.get_size().y + y_pad;

    connect_button
    .set_pos({x_pad, current_y})
    .set_label("Connect")
    .set_idle_color({50,50,50})
    .set_hover_color({60,90,70})
    .set_pressed_color({30,70,50});
}


//**********************************************************************
void login_state::handle_events(const sf::Event& e)
{
    connect_button.handle_events(e);
    address_field.handle_events(e);
    username_field.handle_events(e);

    if (e.type == sf::Event::KeyPressed)
    {
        if(e.key.code == sf::Keyboard::Tab)
        {
            if(username_field.get_active())
            {
                username_field.set_active(false);

                address_field.set_active(true);
            }
            else if(address_field.get_active())
            {
                address_field.set_active(false);

                username_field.set_active(true);
            }
        }
    }
}


//**********************************************************************
void login_state::update()
{
    address_field.update();
    username_field.update();

    if(connect_button.was_triggered())
    {
        std::cout << "Connecting to server ... \n";
        if(connect_to_server(address_field.get_string(), username_field.get_string()))
        {
            change_state("game");
        }
        else
        {
            address_field.clear_buffer();
        }
    }
}


//**********************************************************************
void login_state::draw() const
{
    window.draw(title);
    window.draw(address_label);
    window.draw(username_label);

    address_field.draw();
    username_field.draw();
    connect_button.draw();
}


//**********************************************************************
void login_state::cleanup()
{}


//**********************************************************************
void login_state::startup()
{}

