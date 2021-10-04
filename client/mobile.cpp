
#include "mobile.hpp"
#include <concepts>


//**********************************************************************
mobile::mobile()
{

}


//**********************************************************************
template<typename T> 
requires arithmetic<T>
size_t mobile::get_mod(const T ability_score) const
{
    return static_cast<int>((ability_score - 10) / 2);
}