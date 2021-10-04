
#pragma once

#include <SFML/Graphics.hpp>
#include "text_field.hpp"

class output_field : public text_field
{
    std::vector<sf::Text> line_stack;

    const size_t text_padding = 4;
public:
    void add_line(std::string s, bool add_prompt = true);

    explicit output_field(sf::Font& f, sf::RenderWindow& w, size_t c_size);

    sf::Vector2f get_pos() const override;

    sf::Vector2f get_size() const override;

    void draw() const override;

    void set_size(sf::Vector2f vec) override;

    void set_pos(sf::Vector2f vec) override;

    void update() override;

};