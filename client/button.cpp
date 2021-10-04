#include "button.hpp"


//**********************************************************************
button::button(sf::RenderWindow& window, sf::Font& font, size_t text_size)
    : window {window}
    , font   {font}
{
    label.setFont(font);
    label.setCharacterSize(text_size);
    label.setFillColor(sf::Color::White);
}


//**********************************************************************
void button::handle_events(const sf::Event& e)
{
    if(e.type == sf::Event::MouseMoved && !pressed)
    {
        if(panel.getGlobalBounds().contains( (float) e.mouseMove.x, (float) e.mouseMove.y))
        {
            // mouse is inside button, set to hover
            panel.setFillColor(hover_color);
        }
        else
        {
            // mouse is outside button, set to idle
            panel.setFillColor(idle_color);
        }
    }

    if(e.type == sf::Event::MouseButtonPressed && !pressed)
    {
        if(panel.getGlobalBounds().contains( (float) e.mouseButton.x, (float) e.mouseButton.y))
        {
            // mouse is inside button and pressed, set to pressed
            panel.setFillColor(pressed_color);
            pressed = true;
        }
    }

    if(e.type == sf::Event::MouseButtonReleased)
    {
        if(panel.getGlobalBounds().contains( (float) e.mouseButton.x, (float) e.mouseButton.y))
        {
            // mouse is inside button and not pressed, set to hover
            panel.setFillColor(hover_color);
            triggered = true;
        }
        else
        {
            // mouse is outside button, set to idle
            panel.setFillColor(idle_color);
        }
        pressed = false;
    }
}


//**********************************************************************
void button::update()
{}


//**********************************************************************
void button::draw() const
{
    window.draw(panel);
    window.draw(label);
}


//**********************************************************************
button& button::set_size(const sf::Vector2f& size)
{
    panel.setSize(size);
    update_label_pos();
    return *this;
}


//**********************************************************************
button& button::set_pos(const sf::Vector2f& pos)
{
    panel.setPosition(pos);
    update_label_pos();
    return *this;
}


//**********************************************************************
button& button::set_label(const std::string& label_string)
{
    label.setString(label_string);
    update_label_pos();
    return *this;
}


//**********************************************************************
button& button::set_idle_color(sf::Color color)
{
    idle_color = color;
    return *this;
}


//**********************************************************************
button& button::set_hover_color(sf::Color color)
{
    hover_color = color;
    return *this;
}


//**********************************************************************
button& button::set_pressed_color(sf::Color color)
{
    pressed_color = color;
    return *this;
}


//**********************************************************************
sf::Vector2f button::get_pos() const
{
    return panel.getPosition();
}


//**********************************************************************
sf::Vector2f button::get_size() const
{
    return panel.getSize();
}


//**********************************************************************
bool button::was_triggered()
{
    bool triggered_temp { triggered };
    triggered = false;
    return triggered_temp;
}


//**********************************************************************
void button::update_label_pos()
{
    const auto label_bounds { label.getGlobalBounds() };
    const auto panel_bounds { panel.getGlobalBounds() };

    const float x_pad { (panel_bounds.width - label_bounds.width) / 2.0f };
    const float y_pad { (panel_bounds.height - label_bounds.height) / 2.0f };

    label.setPosition(panel_bounds.left + x_pad , panel_bounds.top + y_pad);
}