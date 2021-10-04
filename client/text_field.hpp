
#pragma once

#include <SFML/Graphics.hpp>

class text_field
{
protected:
    char prompt = '>';

    sf::Glyph prompt_glyph;

    sf::RectangleShape bg;

    sf::Vector2f pos {0,0};

    sf::Vector2f size;

    size_t char_size;

    sf::RenderWindow& window;

    sf::Font& font;

public:

    text_field(sf::Font& f, sf::RenderWindow& w, size_t c_size);

    virtual sf::Vector2f get_pos() const = 0;

    virtual sf::Vector2f get_size() const = 0;

    virtual void draw() const = 0;
 
    virtual void set_size(sf::Vector2f vec) = 0;
 
    virtual void set_pos(sf::Vector2f vec) = 0;

    virtual void update() = 0;
};