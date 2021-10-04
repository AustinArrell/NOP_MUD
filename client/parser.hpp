#include <iostream>
#include <regex>
#include <string>
#include <vector>

class parser
{
    private:
    
        std::string command;

        std::vector<std::string> command_words;

    public:

        void set_command(std::string s);

        void tokenize_command(std::regex reg);

        int count_words(std::vector<std::string>);

        std::vector<std::string> get_command_words();

        bool grammar_check();

};