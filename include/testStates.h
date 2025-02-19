//
// Created by nikolaj on 17/02/25.
//

#ifndef GILGAMESHENGINE_TESTSTATES_H
#define GILGAMESHENGINE_TESTSTATES_H


#include <vector>
#include "stateIndices8bit.h"
#include "valueMatrix8bit_backformat.h"

struct exampleState{
    stateIndices8bit state;
    valueMatrix8bit_backformat matrix;
    int value;

    exampleState(stateIndices8bit _state, valueMatrix8bit_backformat _matrix, int _value):
            state(_state),
            matrix(_matrix),
            value(_value)
            {

            }
};

///@brief Get a number of states, matrices with corresponding values for each state, and future legal states, all manually calculated, (for testing)
std::vector<exampleState> testStates ();


#endif //GILGAMESHENGINE_TESTSTATES_H
