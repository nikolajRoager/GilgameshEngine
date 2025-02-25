#pragma once

#include "stateIndices8bit.h"
#include "valueMatrix8bit_dense_full.h"

///@brief Header to get value from a state with a valueMatrix, will be defined with various algorithms
///@param state the state in the default format
///@param values the value matrix, in the default format
int16_t getValue(stateIndices8bit state, valueMatrix8bit_dense_full values);
