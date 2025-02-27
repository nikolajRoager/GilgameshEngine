//
// Created by nikolaj on 17/02/25.
//

#ifndef GILGAMESHENGINE_STATEINDICES_H
#define GILGAMESHENGINE_STATEINDICES_H

#include <array>
#include <cstdint>

///@brief one way of representing the state of the game at some point, the first 8 numbers represent player 0, the next 8 represents player 1, the first half-byte for each player is 0xF if it is this players turn, otherwise 0, the next half-byte is 0x8 if that player has something at 8 (this ). All the next bytes are 8 bit numbers (this speeds up some calculations), telling us where each piece is, they are generally not assumed to be sorted
template<typename T, typename = std::enable_if<std::is_integral_v<T>> >
struct stateIndices{
    ///@brief the data with state indices, the first 8 bytes represent player 0, the next 8 represents player 1, the first half-byte for each player is 0xF if it is this players turn, otherwise 0, the next half-byte is 0x8 if that player has something at 8 (this ). All the next bytes are 8 bit numbers (this speeds up some calculations), telling us where each piece is, they are generally not assumed to be sorted
    std::array<int8_t,16> data;

    explicit stateIndices(std::array<int8_t,16> _data): data(_data){}

    ///@brief assuming that the data is valid, returns whose turn it is
    ///@return the player whose turn it is as a boolean false= player0, true=player1
    [[nodiscard]] bool turn() const {return (data[0]&0xF0);}

    ///@brief Begin iterator for my data (for range based for loops)
    auto begin()
    {
        return data.begin();
    }
    ///@brief End iterator for my data (for range based for loops)
    auto end()
    {
        return data.end();
    }
};

#endif //GILGAMESHENGINE_STATEINDICES_H
