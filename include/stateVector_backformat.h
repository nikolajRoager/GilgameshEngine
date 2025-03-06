//
// Created by nikolaj on 17/02/25.
//

#pragma once

#include <array>
#include <cstdint>
#include "stateIndices.h"

///@brief A little wrapper for the state of the game, stored as vector, with unstarted and finished in the back
///@brief  The first 14 numbers is the number of pieces player 0 has in position 1,2,... 14
///@brief  The next 14 numbers are the same thing, but for player 1
///@brief  The final 4 are unstarted player 0 pieces, finished player 0, unstarted player 1, and finished player 1
template<typename T, typename = std::enable_if<std::is_integral_v<T>>>
struct stateVector_backformat{
    std::array<T,32> data;

    explicit stateVector_backformat(std::array<T,32> _data): data(_data){}

    ///@brief convert from default format, explicitly declared in header, since this is a template function
    explicit stateVector_backformat(const stateIndices<int8_t>& indices8Bit)
    {
        data ={0};
        for (int i =1; i <8; ++i)
        {
            int pos =indices8Bit.data[i];
            if (pos==0)
                ++data[28];
            else if (pos==15)
                ++data[29];
            else
                ++data[pos-1];
        }
        for (int i =9; i <16; ++i)
        {
            int pos =indices8Bit.data[i]+16;
            if (pos==16)
                ++data[30];
            else if (pos==31)
                ++data[31];
            else
                ++data[pos-3];
        }
    }
};

