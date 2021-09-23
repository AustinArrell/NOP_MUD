
#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "text_field.hpp"

// TODO: Cut, Copy (Highlighting), Paste, Entry History, Ctrl + Arrows, Shift + Arrows, Ctrl + A

class input_field : public text_field
{

    sf::RectangleShape cursor;

    int cursor_offset = 0;

    std::string input_buffer;

    sf::Text input_text;

    sf::Clock clock;

    sf::Int64 cursor_blink_interval = 500;

    bool cursor_visible = true;

public:

    explicit input_field(sf::Font& f, sf::RenderWindow& w, const int& c_size);

    void push_buffer(const char& c);

    void push_buffer(const std::string& s);

    void pop_buffer();

    void set_cursor_offset(int num);

    void set_cursor_offset(sf::Vector2i mouse_pos);

    void send_cursor_home();

    void send_cursor_end();

    void set_size(sf::Vector2f vec);

    void set_pos(sf::Vector2f vec);

    void set_char_size(size_t s);

    size_t get_char_size() const;

    sf::Vector2f get_pos() const;

    sf::FloatRect get_global_bounds() const;

    void draw() const;

    void update();


};