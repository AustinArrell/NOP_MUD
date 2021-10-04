#pragma once

#include "state_manager.hpp"
#include "input_field.hpp"
#include "button.hpp"

#include <SFML/Graphics.hpp>

class login_state : public state
{
    sf::Font& font;
    sf::RenderWindow& window;

    input_field address_field;
    input_field username_field;
    button connect_button;

    sf::Text title;
    sf::Text address_label;
    sf::Text username_label;

public:

    explicit login_state(sf::Font& f, sf::RenderWindow& w);

    virtual void handle_events(const sf::Event& e) override;
    virtual void update() override;
    virtual void draw() const override;
    virtual void cleanup() override;
    virtual void startup() override;
};