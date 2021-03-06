
#include "input_field.hpp"
#include <iostream>
#include <cstdlib>

input_field::input_field(sf::Font& f, sf::RenderWindow& w, size_t c_size) :
    text_field(f,w,c_size)
{

    input_buffer.reserve(100);

    command_history.reserve(150);

    input_text.setFont(font);

    input_text.setCharacterSize(char_size);

    input_text.setString(prompt);

    prompt_glyph = font.getGlyph(prompt,char_size,false);

    cursor.setSize({2,static_cast<float>(char_size)});

    set_size({ static_cast<float>(size.x), static_cast<float>(char_size + 4) }); // +4 for padding

    bg.setFillColor(sf::Color(60,60,60));

    bg.setSize(size);

    bg.setPosition(pos);

    cursor.setFillColor(sf::Color::Green);
}


//**********************************************************************
void input_field::handle_events(const sf::Event& e)
{
    if(e.type == sf::Event::MouseButtonPressed)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            if(bg.getGlobalBounds().contains((float) e.mouseButton.x, (float) e.mouseButton.y))
            {
                active = true;
                send_cursor_end();
            }
        }
    }

    // only handle events if active
    if(!active)
    { return; }

    if (e.type == sf::Event::TextEntered)
    {
        //if backspace is pressed pop off the buffer
        if(e.key.code == 8)
        {
            pop_buffer();
        }
        else if(e.key.code >= 0 && e.key.code <= 127 && std::isprint(e.key.code))
        {
            push_buffer(static_cast<char>(e.key.code));
        }

    }

    if (e.type == sf::Event::KeyPressed)
    {
        if(e.key.control && e.key.code == sf::Keyboard::V)
        {
            push_buffer(sf::Clipboard::getString());
        }
        if (e.key.code == sf::Keyboard::Left)
        {
            set_cursor_offset(1);
        }
        if (e.key.code == sf::Keyboard::Right)
        {
            set_cursor_offset(-1);
        }
        if (e.key.code == sf::Keyboard::Home)
        {
            send_cursor_home();
        }
        if (e.key.code == sf::Keyboard::End)
        {
            send_cursor_end();
        }
        if (e.key.code == sf::Keyboard::Up)
        {
            move_history(true);
        }
        if (e.key.code == sf::Keyboard::Down)
        {
            move_history(false);
        }
    }

    if(e.type == sf::Event::MouseButtonPressed)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            if(bg.getGlobalBounds().contains((float) e.mouseButton.x, (float) e.mouseButton.y))
            {
                // TODO: actually implement
                //set_cursor_offset({ e.mouseButton.x, e.mouseButton.y });
            }
            else
            {
                active = false;
            }
        }
    }
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

    for(const auto& i : s)
    {
        font_glyph = font.getGlyph(i , char_size,false);

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
  
    if(input_text.getGlobalBounds().intersects({static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y), 1.0f,1.0f}))

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
    clock.restart();
    
    cursor_visible = true;

    cursor.setPosition(pos.x + prompt_glyph.advance , pos.y);
    
    cursor_offset = input_buffer.size();
}


//**********************************************************************
void input_field::send_cursor_end()
{
    clock.restart();
    
    cursor_visible = true;

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
void input_field::set_size(sf::Vector2f vec)
{
    size = vec;

    bg.setSize( vec );
}


//**********************************************************************
void input_field::set_char_size(size_t s)
{
    char_size = s;
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

std::string input_field::get_string() const
{
    return input_buffer;
}


//**********************************************************************
void input_field::clear_buffer()
{
    input_buffer.clear();

    input_text.setString(prompt);

    send_cursor_home();

}


//**********************************************************************
void input_field::draw() const
{

    window.draw(bg);

    window.draw(input_text);

    if(cursor_visible && active)
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


//**********************************************************************
sf::Vector2f input_field::get_size() const
{
    return size;
}


//**********************************************************************
 void input_field::move_history(bool up)
 {
     if(command_history.size() > 0)
     {
        if(up && history_offset < command_history.size())
        {
            history_offset += 1;

            input_buffer.clear();

            send_cursor_home();

            push_buffer(command_history.rbegin()[history_offset - 1]);

        }else if(!up && history_offset > 1)
        {
            history_offset -= 1;

            input_buffer.clear();

            send_cursor_home();

            push_buffer(command_history.rbegin()[history_offset - 1]);
        }

     }

 }


//**********************************************************************
void input_field::push_history(std::string s)
{
    history_offset = 0;
    
    command_history.push_back(s);
}


//**********************************************************************
void input_field::set_active(bool b)
{
    active = b;
}


//**********************************************************************
bool input_field::get_active() const
{
    return active;
}