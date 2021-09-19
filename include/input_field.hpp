
#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class input_field
{
    char prompt;

    sf::RectangleShape bg;

    sf::RectangleShape cursor;

    int cursor_offset = 0;

    sf::Vector2f pos {0,0};

    sf::Vector2f size;

    std::string input_buffer;

    sf::Font font; // TODO: Move font to main

    std::string font_path;

    size_t char_size;

    sf::Text input_text;

    sf::RenderWindow& window;

public:

    explicit input_field(sf::RenderWindow& w); // Explicit avoids implicit conversions

    void push_buffer(char c);

    void pop_buffer();

    void set_cursor_offset(int num);

    void send_cursor_home();

    void send_cursor_end();

    void set_pos(sf::Vector2f vec);

    void set_pos(float x, float y);

    void set_size(sf::Vector2f vec);

    void set_size(float x, float y);

    void draw();

    void update();

};