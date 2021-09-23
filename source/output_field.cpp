
#include "output_field.hpp"


//**********************************************************************
output_field::output_field(sf::Font& f, sf::RenderWindow& w, const int& c_size) :
    text_field(f, w, c_size)
{
    bg.setFillColor(sf::Color(60,60,60));

    bg.setSize( {static_cast<float>(size.x), static_cast<float>(char_size + 2)} ); // +2 for padding

    bg.setPosition(pos);
}


//**********************************************************************
void output_field::draw() const
{
    window.draw(bg);
}


//**********************************************************************
void output_field::set_size(sf::Vector2f vec)
{

}


//**********************************************************************
void output_field::set_pos(sf::Vector2f vec)
{

}


//**********************************************************************
void output_field::update()
{

}