//
// Created by nikolaj on 17/02/25.
//

#ifndef GILGAMESHENGINE_TESTSTATES_H
#define GILGAMESHENGINE_TESTSTATES_H


#include <vector>
#include "stateIndices.h"
#include "valueMatrix_dense_3of4_backformat.h"
#include "valueMatrix_dense_full.h"

///@brief A package which includes a state, and a value matrix, and the known values betwixt these, used for testing
struct exampleState{
    stateIndices<int8_t> state;
    valueMatrix_dense_full<int8_t> matrix;
    int value;

    exampleState(stateIndices<int8_t> _state, valueMatrix_dense_full<int8_t> _matrix, int _value):
            state(_state),
            matrix(_matrix),
            value(_value)
            {

            }
};

///@brief Get a number of states, matrices with corresponding values for each state, and future legal states, all manually calculated, (for testing)
std::vector<exampleState> testStates ();


#endif //GILGAMESHENGINE_TESTSTATES_H
