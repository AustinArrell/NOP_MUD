
#include "output_field.hpp"

#include <iostream>


//**********************************************************************
output_field::output_field(sf::Font& f, sf::RenderWindow& w, const int& c_size) :
    text_field(f, w, c_size)
{
    line_stack.reserve(40);

    bg.setFillColor(sf::Color(60,60,60));
}


//**********************************************************************
void output_field::add_line(std::string s, bool add_prompt)
{
    // Create a new sf::Text and place it into line_stack
    if(add_prompt)
    {
        line_stack.emplace_back(prompt + s , font, char_size);
    }else
    {
        line_stack.emplace_back(s , font, char_size);
    }

    // Creating variables for readability
    size_t stack_size = line_stack.size();
    sf::Text& last_line = line_stack.back();
    
    // Set text position
    if(stack_size > 1)
    {
        const sf::Text& previous_line = line_stack.rbegin()[1];

        last_line.setPosition(previous_line.getPosition().x , previous_line.getPosition().y + char_size);
    }else
    {
        last_line.setPosition(pos.x, pos.y + text_padding);
    }

    //validate string length
    if(last_line.findCharacterPos(last_line.getString().getSize()).x > size.x + pos.x)
    {
        std::string remainder_str;

        std::string current_str = last_line.getString();

        for(int i = 0; i < current_str.size(); i++)
        {
            if (last_line.findCharacterPos(i).x > size.x + pos.x - font.getGlyph(last_line.getString()[i], char_size, false).advance - text_padding)
            {
                int last_space_index = i;
                
                // Look for the last space character.
                while(last_line.getString()[last_space_index] != 32)
                {
                    last_space_index -= 1;
                }

                // If no space character exists just wrap the text by character
                if ( last_space_index <= 0)
                {
                    remainder_str = current_str.substr(i, current_str.size()-1);

                    last_line.setString(current_str.substr(0,i));
                
                // If a space character exists wrap the text by word
                }else
                {
                    remainder_str = current_str.substr(last_space_index, current_str.size()-1);

                    last_line.setString(current_str.substr(0,last_space_index));
                }

                // Recurse until the line fits
                add_line("\t" + remainder_str, false);
                
                break;
            }
        }
    }
}


//**********************************************************************
void output_field::draw() const
{
    window.draw(bg);

    for(const auto& i : line_stack)
    {
        window.draw(i);
    }
}


//**********************************************************************
void output_field::set_size(sf::Vector2f vec)
{
    size = vec;

    bg.setSize(size);
}


//**********************************************************************
void output_field::set_pos(sf::Vector2f vec)
{
    pos = vec;

    bg.setPosition(pos);
}


//**********************************************************************
void output_field::update()
{

}


//**********************************************************************
sf::Vector2f output_field::get_size() const
{
    return size;
}


//**********************************************************************
sf::Vector2f output_field::get_pos() const
{
    return pos;
}

