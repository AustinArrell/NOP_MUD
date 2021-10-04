#include "parser.hpp"
#include "verbs.hpp"
#include "nouns.hpp"

void parser::set_command(std::string s)
{
    command = s;
}

void parser::tokenize_command(std::regex reg)
{
    std::sregex_token_iterator iter(command.begin(), command.end(), reg, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> tokenized(iter, end);

    command_words = tokenized;
}


int parser::count_words(std::vector<std::string> tcommand)
{
    return tcommand.size();
}

std::vector<std::string> parser::get_command_words()
{
    return command_words;
}

bool parser::grammar_check()
{
    if(command_words.size() == 1 && is_verb(command_words.at(0)))
    {
        switch (get_command_from_verb(command_words.at(0)))
        {
        case command_type::GO_NORTH:
                return true;
            break;
        
        case command_type::GO_SOUTH:
                return true;
            break;

        case command_type::GO_EAST:
                return true;
            break;

        case command_type::GO_WEST:
                return true;
            break;

        case command_type::GO_UP:
                return true;
            break;

        case command_type::GO_DOWN:
                return true;
            break;

        case command_type::LOOK:
                return true;
            break;
        
        default:
                return false;
            break;
        }
    }
    else if (command_words.size() == 2 && is_verb(command_words.at(0)) && is_noun(command_words.at(1)))
    {
        switch (get_command_from_verb(command_words.at(0)))
        {
        case command_type::GET:
            switch (get_command_from_noun(command_words.at(1)))
            {
            case noun_type::ITEM:
                return true;
                break;
            
            default:
                return false;
                break;
            }
            break;

        case command_type::LOOK:
            switch (get_command_from_noun(command_words.at(1)))
            {
            case noun_type::NORTH_DIRECTION:
                return true;
                break;
            
            case noun_type::SOUTH_DIRECTION:
                return true;
                break;

            case noun_type::EAST_DIRECTION:
                return true;
                break;

            case noun_type::WEST_DIRECTION:
                return true;
                break;

            case noun_type::UP_DIRECTION:
                return true;
                break;

            case noun_type::DOWN_DIRECTION:
                return true;
                break;

            default:
                return false;
                break;
            }
            break;

        case command_type::GO:
            switch (get_command_from_noun(command_words.at(1)))
            {
            case noun_type::NORTH_DIRECTION:
                return true;
                break;
            
            case noun_type::SOUTH_DIRECTION:
                return true;
                break;

            case noun_type::EAST_DIRECTION:
                return true;
                break;

            case noun_type::WEST_DIRECTION:
                return true;
                break;

            case noun_type::UP_DIRECTION:
                return true;
                break;

            case noun_type::DOWN_DIRECTION:
                return true;
                break;

            default:
                return false;
                break;
            }
            break;

        default:
            return false;
            break;
        }
    }
    else if (
        command_words.size() >= 3 &&
            (
                get_command_from_verb(command_words.at(0)) == command_type::SPEAK_LOCAL ||
                get_command_from_verb(command_words.at(0)) == command_type::SPEAK_ZONE ||
                get_command_from_verb(command_words.at(0)) == command_type::SPEAK_GLOBAL
            )
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}