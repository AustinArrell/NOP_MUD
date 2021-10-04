
#pragma once

#include <map>
#include <string>
#include <concepts>

template<typename T>
concept arithmetic = std::integral<T>;

class mobile
{
        std::map<std::string, size_t> ability_scores = 
        {
            {"str" , 10},
            {"dex" , 10},
            {"con" , 10},
            {"int" , 10},
            {"wis" , 10},
            {"cha" , 10},
        };

    public:

        mobile();

        template<typename T>
        requires arithmetic<T>
        size_t get_mod(const T ability_score) const;
    
};