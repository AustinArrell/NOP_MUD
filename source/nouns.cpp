#include "nouns.hpp"

std::map<std::string, noun_type> noun_map = {
    {"north", noun_type::NORTH_DIRECTION},
    {"n", noun_type::NORTH_DIRECTION},
    {"south", noun_type::SOUTH_DIRECTION},
    {"s", noun_type::SOUTH_DIRECTION},
    {"east", noun_type::EAST_DIRECTION},
    {"e", noun_type::EAST_DIRECTION},
    {"west", noun_type::WEST_DIRECTION},
    {"w", noun_type::WEST_DIRECTION},
    {"up", noun_type::UP_DIRECTION},
    {"u", noun_type::UP_DIRECTION},
    {"down", noun_type::DOWN_DIRECTION},
    {"d", noun_type::DOWN_DIRECTION},
    {"item", noun_type::ITEM},
    {"", noun_type::INVALID}
};

bool is_noun(const std::string& word)
{
    if(noun_map.find(word) != noun_map.end())
    {
        return true;
    }
    else 
    {
        return false;
    }
}

noun_type get_command_from_noun(const std::string& word)
{
    if(is_noun(word))
    {
        return noun_map.find(word)->second;
    }
    else
    {
        return noun_type::INVALID;
    }
}