//
// Created by nikolaj on 17/02/25.
//

#include "testStates.h"

///@brief Get a number of state index type states for testing
std::vector<exampleState> testStates ()
{
    stateIndices8bit out({
             //The (int8_t) are there to silence compiler warnings
             (int8_t)0xF0,//Player 0 turn
             (int8_t)0x0,(int8_t)0x0,(int8_t)0x3,(int8_t)0x4,(int8_t)0xD,(int8_t)0x6,(int8_t)0xE,
             (int8_t)0x08,//There is a piece at 8
             (int8_t)0x0,(int8_t)0x1,(int8_t)0x2,(int8_t)0x3,(int8_t)0x5,(int8_t)0x8,(int8_t)0xF,
         });


    return {exampleState(out,valueMatrix8bit_backformat(),0)};
}
