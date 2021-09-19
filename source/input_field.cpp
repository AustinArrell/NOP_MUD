
#include "input_field.hpp"
#include <iostream>

input_field::input_field(sf::RenderWindow& w) :
    window {w},
    size {w.getSize()},
    prompt {'>'}

{

    input_buffer.reserve(100);

    font.loadFromFile("../resources/fonts/Roboto-Black.ttf");

    input_text.setFont(font);

    input_text.setCharacterSize(20);

    char_size = input_text.getCharacterSize();

    input_text.setFillColor(sf::Color::White);

    cursor.setFillColor(sf::Color::White);

    cursor.setSize({char_size,char_size});
}

void input_field::push_buffer(char c)
{
    input_buffer.insert(input_buffer.end() - cursor_offset,c);

    input_text.setString(input_buffer);

    cursor.setPosition(cursor.getPosition().x + char_size, cursor.getPosition().y);
}

void input_field::pop_buffer()
{
    if(input_buffer.size() > 0 && cursor_offset < input_buffer.size())
    {
        input_buffer.erase(input_buffer.end()-1-cursor_offset);

        input_text.setString(input_buffer);

        cursor.setPosition(cursor.getPosition().x - char_size, cursor.getPosition().y);
    }

}

void input_field::set_cursor_offset(int num)
{
    // Move the cursor based on the offset, assuming we are within the bounds of the input_text
    if (cursor_offset + num > -1 && cursor_offset + num < input_buffer.size()+1)
    {
        cursor_offset += num;

        if(num > 0)
        {
            cursor.setPosition(cursor.getPosition().x - char_size , cursor.getPosition().y);
        }else
        {
            cursor.setPosition(cursor.getPosition().x + char_size , cursor.getPosition().y);
        }
    }

}

void input_field::send_cursor_home()
{

}

void input_field::send_cursor_end()
{


}

void input_field::set_pos(sf::Vector2f vec)
{
    pos = vec;
}

void input_field::set_pos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}

void input_field::set_size(sf::Vector2f vec)
{
    size = vec;
}

void input_field::set_size(float x, float y)
{
    size.x = x;
    size.y = y;
}

void input_field::draw()
{
    window.draw(input_text);

    window.draw(cursor);
}

void input_field::update()
{

}