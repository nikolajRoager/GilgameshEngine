//
// Created by nikolaj on 17/02/25.
//

#ifndef GILGAMESHENGINE_STATEVECTOR_H
#define GILGAMESHENGINE_STATEVECTOR_H


#include <array>
#include <cstdint>
#include "stateIndices.h"

///@brief A little wrapper for the state of the game, stored as vector, in default order
///@brief  The first 16 numbers is the number of pieces player 0 has in position 0,1,2,... 15 (where 15 is the goal, and 0 is the home)
///@brief  The next 16 numbers are the same thing, but for player 1
template<typename T, typename = std::enable_if<std::is_integral_v<T>>>
struct stateVector{
    std::array<T,32> data;

    explicit stateVector(std::array<T,32> _data): data(_data){}

    ///@brief convert from default format, explicitly declared in header, since this is a template function
    explicit stateVector(const stateIndices<int8_t>& indices8Bit)
    {
        data ={0};
        for (int i =1; i <8; ++i)
            ++data[indices8Bit.data[i]];
        for (int i =9; i <16; ++i)
            ++data[indices8Bit.data[i]+16];
    }
};


#endif //GILGAMESHENGINE_STATEVECTOR_H
