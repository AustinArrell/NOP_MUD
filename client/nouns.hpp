#include <map>
#include <string>

enum class noun_type {
    NORTH_DIRECTION,
    SOUTH_DIRECTION,
    EAST_DIRECTION,
    WEST_DIRECTION,
    UP_DIRECTION,
    DOWN_DIRECTION,
    ITEM,
    INVALID
};

bool is_noun(const std::string& word);
noun_type get_command_from_noun(const std::string& word);