#pragma once

#include "stateIndices.h"
#include <string>
#include "valueMatrix8bit_dense_full.h"

///@brief Convert the default state format to a pointer to the data-start in the format we want to use (Polymorphism is bad for performance)
void* loadStateWorkspace(const stateIndices<int8_t> & state);
///@brief Convert the default matrix  format to a pointer to the data-start in the format we want to use (Polymorphism is bad for performance)
void* loadMatrixWorkspace(const valueMatrix8bit_dense_full& matrix);

///@brief Free the workspace used for this algorithm, assuming we have loaded it
void freeWorkspace(void* stateAddress, void* matrixAddress);

///@brief Header to get value from a state with a valueMatrix, will be defined with various algorithms
///@param state_ptr a pointer to the start of the data of the state, in whatever format this implementation uses (use loadStateWorkspace to ensure the format is correct).
///@param matrix_ptr a pointer to the start of the data of the value matrix, in whatever format this implementation uses (use loadMatrixWorkspace to ensure the format is correct).
///@return a 32 bit integer, storing the value of the current state given the matrix, 32 bit is always large enough to store the value (assuming that the matrix is constrained to 8 bit integers)
///@warning Undefined behaviour if the pointers do not point to the data format created by the loadStateWorkspace functions
int32_t getValue(const void* state_ptr,const void* matrix_ptr);

///@brief for displaying what algorithm we are testing
std::string algorithmDescription();

///@brief If true, then this algorithm is not intended to produce the correct result, and should be ignored in tests
bool ignoreOutput();