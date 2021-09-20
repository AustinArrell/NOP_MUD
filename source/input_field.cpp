
#include "input_field.hpp"
#include <iostream>
#include <cstdlib>

input_field::input_field(sf::Font& f, sf::RenderWindow& w) :
    size { w.getSize() },
    prompt {'>'},
    font {f},
    window {w}

{
    input_buffer.reserve(100);

    input_text.setFont(font);

    input_text.setCharacterSize(14);

    input_text.setString(prompt);

    char_size = input_text.getCharacterSize();

    prompt_glyph = font.getGlyph(prompt,char_size,false);

    cursor.setSize({3,static_cast<float>(char_size)});

    bg.setFillColor(sf::Color(60,60,60));

    bg.setSize( {static_cast<float>(size.x), static_cast<float>(char_size + 2)} ); // +2 for padding

    bg.setPosition(pos);

    cursor.setFillColor(sf::Color::Green);
}


//**********************************************************************
void input_field::push_buffer(const char& c)
{
    clock.restart();
    cursor_visible = true;
    
    sf::Glyph font_glyph = font.getGlyph(c,char_size,false);

    if(input_text.getLocalBounds().width + font_glyph.advance < size.x - cursor.getLocalBounds().width)
    {
        input_buffer.insert(input_buffer.end() - cursor_offset,c);

        input_text.setString(prompt + input_buffer);

        cursor.setPosition(cursor.getPosition().x + font_glyph.advance, cursor.getPosition().y);
    }

}


//**********************************************************************
void input_field::push_buffer(const std::string& s)
{
    clock.restart();
    cursor_visible = true;

    float advance = 0;
    sf::Glyph font_glyph;

    for(size_t i = 0; i < s.size(); i++)
    {
        font_glyph = font.getGlyph(s.at(i) , char_size,false);

        advance += font_glyph.advance;
    }
    

    if(input_text.getLocalBounds().width + advance < size.x - cursor.getLocalBounds().width)
    {
        input_buffer.insert(input_buffer.size() - cursor_offset , s);

        input_text.setString(prompt + input_buffer);

        cursor.setPosition(cursor.getPosition().x + advance, cursor.getPosition().y);
    }

}


//**********************************************************************
void input_field::pop_buffer()
{
    clock.restart();
    cursor_visible = true;

    if(input_buffer.size() > 0 && cursor_offset < input_buffer.size())
    {
        sf::Glyph font_glyph = font.getGlyph(input_buffer.at(input_buffer.size()-1-cursor_offset),char_size,false); // -1 to get character behind cursor

        input_buffer.erase(input_buffer.end()-1-cursor_offset);

        input_text.setString(prompt + input_buffer);

        cursor.setPosition(cursor.getPosition().x - font_glyph.advance, cursor.getPosition().y);
    }

}


//**********************************************************************
void input_field::set_cursor_offset(int num)
{
    clock.restart();
    cursor_visible = true;

    // Move the cursor based on the offset, assuming we are within the bounds of the input_text
    if (cursor_offset + num > -1 && cursor_offset + num < input_buffer.size()+1)
    {
        cursor_offset += num;

        if(num > 0)
        {
            // Find the size of the glyph to the left of the cursor
            sf::Glyph font_glyph = font.getGlyph(input_buffer.at(input_buffer.size()-cursor_offset),char_size,false);

            cursor.setPosition(cursor.getPosition().x - font_glyph.advance , cursor.getPosition().y);
        }else
        {
            // Find the size of the glyph to the right of the cursor
            sf::Glyph font_glyph = font.getGlyph(input_buffer.at(input_buffer.size()-cursor_offset-1),char_size,false);

            cursor.setPosition(cursor.getPosition().x + font_glyph.advance , cursor.getPosition().y);
        }
    }
}


//**********************************************************************
void input_field::set_cursor_offset(sf::Vector2i mouse_pos)
{
    clock.restart();
    cursor_visible = true;

    if(input_text.getGlobalBounds().intersects({mouse_pos.x, mouse_pos.y, 1,1}))
    {
        cursor.setPosition(mouse_pos.x, cursor.getPosition().y);

        size_t closest_index = 0;

        size_t closest_distance = 10000;

        for(size_t i; i < input_buffer.size(); i++)
        {   
            if (std::abs(input_text.findCharacterPos(i).x - mouse_pos.x) < closest_distance)
            {
                closest_distance = std::abs(input_text.findCharacterPos(i).x - mouse_pos.x);
                closest_index = i;
            }   
        }
        std::cout<<"Closest Index:" << closest_index << "\n";
    }
}


//**********************************************************************
void input_field::send_cursor_home()
{
    cursor.setPosition(pos.x + prompt_glyph.advance , pos.y);
    
    cursor_offset = input_buffer.size();
}


//**********************************************************************
void input_field::send_cursor_end()
{
    cursor.setPosition(pos.x + input_text.getGlobalBounds().width , pos.y);
    
    cursor_offset = 0;
}


//**********************************************************************
void input_field::set_pos(sf::Vector2f vec)
{
    pos = vec;

    bg.setPosition(pos);

    input_text.setPosition(pos);

    cursor.setPosition(pos.x + prompt_glyph.advance , pos.y);
}


//**********************************************************************
void input_field::set_pos(float x, float y)
{
    pos.x = x;
    pos.y = y;

    bg.setPosition(pos);
    
    input_text.setPosition(pos);

    cursor.setPosition(pos.x + prompt_glyph.advance , pos.y);

}


//**********************************************************************
void input_field::set_size(sf::Vector2f vec)
{
    size = vec;

    bg.setSize( {static_cast<float>(size.x), static_cast<float>(char_size + 2)} ); // +2 for padding
}


//**********************************************************************
void input_field::set_size(float x, float y)
{
    size.x = x;
    size.y = y;

    bg.setSize( {static_cast<float>(size.x), static_cast<float>(char_size + 2)} ); // +2 for padding
}


//**********************************************************************
size_t input_field::get_char_size() const
{
    return char_size;
}

//**********************************************************************
sf::Vector2f input_field::get_pos() const
{
    return pos;
}

//**********************************************************************
sf::FloatRect input_field::get_global_bounds() const
{   
    return bg.getGlobalBounds();
}

//**********************************************************************
void input_field::draw() const
{
    
    window.draw(bg);

    window.draw(input_text);

    if(cursor_visible)
    {
        window.draw(cursor);
    }
    
}

//**********************************************************************
void input_field::update()
{
    if(clock.getElapsedTime().asMilliseconds() >= cursor_blink_interval)
    {
        clock.restart();
        cursor_visible = !cursor_visible;
    }
}