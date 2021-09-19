
#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

// TODO: Cut, Copy (Highlighting), Paste, Entry History, Ctrl + Arrows, Shift + Arrows, Ctrl + A

class input_field
{
    char prompt;

    sf::RectangleShape bg;

    sf::RectangleShape cursor;

    int cursor_offset = 0;

    sf::Vector2f pos {0,0};

    sf::Vector2f size;

    std::string input_buffer;

    sf::Font& font;

    size_t char_size;

    sf::Text input_text;

    sf::RenderWindow& window;

    sf::Glyph prompt_glyph;

    sf::Clock clock;

    sf::Int64 cursor_blink_interval = 500;

    bool cursor_visible = true;

public:

    explicit input_field(sf::RenderWindow& w, sf::Font& f); // Explicit avoids implicit conversions

    void push_buffer(const char& c);

    void push_buffer(const std::string& s);

    void pop_buffer();

    void set_cursor_offset(int num);

    void send_cursor_home();

    void send_cursor_end();

    void set_pos(sf::Vector2f vec);

    void set_pos(float x, float y);

    void set_size(sf::Vector2f vec);

    void set_size(float x, float y);

    size_t get_char_size() const;

    void draw() const;

    void update();

};