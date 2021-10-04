#include <map>
#include <string>

enum class command_type {
    GET,
    PUT,
    GO,
    GO_NORTH,
    GO_SOUTH,
    GO_EAST,
    GO_WEST,
    GO_UP,
    GO_DOWN,
    LOOK,
    SPEAK_LOCAL,
    SPEAK_ZONE,
    SPEAK_GLOBAL,
    INVALID
};

bool is_verb(const std::string& word);
command_type get_command_from_verb(const std::string& word);