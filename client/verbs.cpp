#include "verbs.hpp"

std::map<std::string, command_type> verb_map = {
    {"get", command_type::GET},
    {"pickup", command_type::GET},
    {"put", command_type::PUT},
    {"place", command_type::PUT},
    {"go", command_type::GO},
    {"north", command_type::GO_NORTH},
    {"n", command_type::GO_NORTH},
    {"south", command_type::GO_SOUTH},
    {"s", command_type::GO_SOUTH},
    {"east", command_type::GO_EAST},
    {"e", command_type::GO_EAST},
    {"west", command_type::GO_WEST},
    {"w", command_type::GO_WEST},
    {"up", command_type::GO_UP},
    {"u", command_type::GO_UP},
    {"down", command_type::GO_DOWN},
    {"d", command_type::GO_DOWN},
    {"look", command_type::LOOK},
    {"say", command_type::SPEAK_LOCAL},
    {"yell", command_type::SPEAK_ZONE},
    {"chat", command_type::SPEAK_GLOBAL},
    {"", command_type::INVALID}
};

bool is_verb(const std::string& word)
{
    if(verb_map.find(word) != verb_map.end())
    {
        return true;
    }
    else 
    {
        return false;
    }
}

command_type get_command_from_verb(const std::string& word)
{
    if(is_verb(word))
    {
        return verb_map.find(word)->second;
    }
    else
    {
        return command_type::INVALID;
    }
}