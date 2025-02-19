//
// Created by nikolaj on 17/02/25.
//

#ifndef GILGAMESHENGINE_STATEVECTOR_H
#define GILGAMESHENGINE_STATEVECTOR_H


#include <array>
#include <cstdint>

///A little wrapper for the state of the game, stored as a 16 bit vector
///The first 14 numbers are  player 0's number of pieces at position 1,2,3,...14 (0 or 1)
/// The next 32 bytes is the number of pieces player 0 has in position 0,1,2,... 15 (where 15 is the goal, and 0 is the home)
/// The next 32 bytes are the same thing, but for player 1
/// Storing the number of pieces on the board as 16 bit number might seem wasteful, but this way we won't have to perform expensive casts when summing up the value
/// This comes with a few attached helper functions
struct stateVector16 {
    std::array<int16_t,33> data;

    explicit stateVector16(std::array<int16_t,33> _data): data(_data){}

    ///Is it currently player 0's turn
    bool player0Turn() { return data[0];}

    int16_t* player0state() {return &data[1];}
    int16_t* player1state() {return &data[18];}
};


#endif //GILGAMESHENGINE_STATEVECTOR_H
