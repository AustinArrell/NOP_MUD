
#pragma once

#include "state_manager.hpp"
#include "input_field.hpp"
#include "output_field.hpp"
#include <SFML/Graphics.hpp>

class game_state : public state
{
    sf::Font& font;

    input_field input_f;

    output_field output_f1;

    output_field output_f2;

    output_field output_f3;

    sf::Vector2i mouse_pos;

    sf::RenderWindow& window;

    int char_size = 14;


public:
    explicit game_state(sf::Font& f, sf::RenderWindow& w);

    virtual void handle_events(const sf::Event& e) override;
    
    virtual void update() override;

    virtual void draw()const override;

    virtual void cleanup() override;

    virtual void startup() override;
};