
#pragma once

#include <SFML/Graphics.hpp>
#include "text_field.hpp"

class output_field : public text_field
{    
    std::vector<sf::Text> line_stack;

    const size_t text_padding = 4;

    void wrap_x(sf::Text& last_line);

    void wrap_y();

public:
    void add_line(std::string s, bool add_prompt = true);

    explicit output_field(sf::Font& f, sf::RenderWindow& w, const int& c_size); 

    sf::Vector2f get_pos() const override;

    sf::Vector2f get_size() const override;

    void scroll_up();

    void scroll_down();

    void draw() const override;

    void set_size(sf::Vector2f vec) override;

    void set_pos(sf::Vector2f vec) override;

    bool intersects(sf::Vector2i& point);

    void update() override;

};