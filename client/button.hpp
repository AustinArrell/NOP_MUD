#pragma once

#include <SFML/Graphics.hpp>

class button
{
    sf::RenderWindow& window;
    sf::Font& font;

    sf::RectangleShape panel;
    sf::Text label;

    sf::Color idle_color    {sf::Color::Black};
    sf::Color hover_color   {sf::Color::Black};
    sf::Color pressed_color {sf::Color::Black};

    bool pressed {false};
    bool triggered {false};

public:

    button(sf::RenderWindow& window, sf::Font& font, size_t text_size);

    void handle_events(const sf::Event& e);
    void update();
    void draw() const;

    button& set_size(const sf::Vector2f& size);
    button& set_pos(const sf::Vector2f& pos);
    button& set_label(const std::string& label_string);

    button& set_idle_color(sf::Color color);
    button& set_hover_color(sf::Color color);
    button& set_pressed_color(sf::Color color);

    sf::Vector2f get_pos() const;
    sf::Vector2f get_size() const;

    bool was_triggered();

private:

    void update_label_pos();
};