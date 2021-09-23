
#pragma once

#include <SFML/Graphics.hpp>
#include "text_field.hpp"

class output_field : public text_field
{    
   

public:

    explicit output_field(sf::Font& f, sf::RenderWindow& w, const int& c_size);

    void draw() const;

    void set_size(sf::Vector2f vec);

    void set_pos(sf::Vector2f vec);

    void update();

};