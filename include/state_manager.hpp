
#pragma once

#include "SFML/Graphics.hpp"

class state
{
public:
    virtual void handle_events(const sf::Event& e) = 0;
    
    virtual void update() = 0;

    virtual void draw() const = 0;

    virtual void cleanup() = 0;

    virtual void startup() = 0;

    virtual ~state() = default;
};

void add_state(std::string name, state& s);

void handle_events(const sf::Event& e);

void change_state(std::string s);

void update_state();

void render_state();