
#include "text_field.hpp"

text_field::text_field(sf::Font& f, sf::RenderWindow& w, size_t c_size) :
    size { w.getSize() },
    font {f},
    window {w},
    char_size {c_size}
{

}