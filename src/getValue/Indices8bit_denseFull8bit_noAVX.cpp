//
// Created by nikolaj on 23/02/25.
//
// Version which uses 8 bit state indices for state, 8bit dense full value matrix in default format
#include <cstdint>
#include <tuple>
#include "stateIndices8bit.h"
#include "valueMatrix8bit_dense_full.h"
#include "getValue.h"

///@brief The best I can do, without using AVX: Use state indices to look up matching values in the matrix
int16_t getValue(stateIndices8bit state, valueMatrix8bit_dense_full matrix)
{
    //I use regular sized ints, because smaller ints (int8_t, int16_t etc. are NOT FASTER in my tests)
    //The only reason to use them, is so that everything fits into an embedded system, or the state fits into a 256 bit AVX register
    //But temporary variables are really not a huge drain on memory, and this version does not use AVX
    int sum = 0;

    //Loop through the 14 indices representing the 7 pieces of either player
    for (int i = 1; i <15; ++i) {
        //Skip the turn-marker bit
        if (i==8)
            i=9;

        int index0 = state.data[i];
        for (int j = 1; j <15; ++j) {
            //Skip the turn-marker bit
            if (j==8)
                j=9;

            //Add 16, since this state index format has both players going from position 0 to 15, but t he matrix has player 1 from 16 to 31
            int index1 = state.data[j]+16;

            //<<5 is a cheaper way of multiplying with 32, don't worry about overflow,
            sum += matrix[index0 * 32 + index1];
        }
    }
    return sum;
}
