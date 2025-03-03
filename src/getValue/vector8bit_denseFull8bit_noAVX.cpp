//
// Created by nikolaj on 27/02/25.
//
#include <cstdint>
#include <tuple>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include "stateIndices.h"
#include "valueMatrix_dense_full.h"
#include "getValue.h"
#include "stateVector.h"

///@brief the conceptually simplest way of getting the value: just use a matrix multiplication with a couple for-loops
int32_t getValue(const void* state_ptr,const void* matrix_ptr)
{
    int sum = 0;
    const auto* state = static_cast<const int8_t*>(state_ptr);
    const auto* matrix= static_cast<const int8_t*>(matrix_ptr);

    for (int i = 0; i < 32; ++i)
        if (state[i]!=0)
            for (int j = i; j < 32; ++j)
                if (state[j]!=0)
                    //I use explicit casts, mainly to help me remember which is what
                    sum+=static_cast<int>(matrix[i+j*32])*static_cast<int>(state[i])*static_cast<int>(state[j]);
    return sum;
}

void* loadStateWorkspace(const stateIndices<int8_t>& state)
{
    auto newState = stateVector<int8_t>(state);
    //Now copy that into a new address so it won't get freed
    void* out = malloc(sizeof (int8_t)*newState.data.size());
    memcpy(out,&(newState.data[0]),sizeof (int8_t)*newState.data.size());
    return out;
}
///@brief Convert the default matrix  format to a pointer to the data-start in the format we want to use (Polymorphism is bad for performance)
void* loadMatrixWorkspace(const valueMatrix_dense_full<int8_t>& matrix)
{
    //just copy the data and return it
    auto out = malloc(matrix.byteSize());
    memcpy(out,matrix.data(),matrix.byteSize());
    return out;
}

///@brief Free the workspace used for this algorithm, assuming we have loaded it
void freeWorkspace(void* stateAddress, void* matrixAddress)
{
    free(stateAddress);
    free(matrixAddress);
}
///@brief for displaying what algorithm we are testing
std::string algorithmDescription()
{
    return "8-bit state vector, with full 8bit dense value matrix without AVX";
}

bool ignoreOutput() {return false;}