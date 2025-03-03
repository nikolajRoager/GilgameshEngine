//
// Created by nikolaj on 23/02/25.
//
// Version which uses 8 bit state indices for state, 8bit dense full value matrix in default format
#include <cstdint>
#include "stateIndices.h"
#include "valueMatrix_dense_full.h"
#include "getValue.h"
#include <cstdlib>
#include <cstring>
#include <string>

///@brief The most readable I can make the algorithm where the state indices are read and translated to a location in the matrix, it is faster than state vector based version, but not as fast as the fully unrolled version
int32_t getValue(const void* state_ptr,const void* matrix_ptr)
{
    //We ASSUME the state and matrix data has been initialized correctly
    const auto* state = static_cast<const int8_t*>(state_ptr);
    const auto* matrix= static_cast<const int8_t*>(matrix_ptr);
    int sum = 0;

    //Loop through the 14 indices representing the 7 pieces of either player
    for (int i = 1; i <16; ++i) {
        //Skip the turn-marker bit
        if (i==8)
            i=9;

        int index0 = state[i] + (i>8?16:0);
        for (int j = 1; j <16; ++j) {
            //Skip the turn-marker bit
            if (j==8)
                j=9;

            //Add 16, since this state index format has both players going from position 0 to 15, but t he matrix has player 1 from 16 to 31
            int index1 = state[j] + (j>8?16:0);


            sum += matrix[index0 * 32 + index1];
        }
    }
    return static_cast<int16_t>(sum);
}

void* loadStateWorkspace(const stateIndices<int8_t>& state)
{
    //just copy the data and return it
    auto out = malloc(state.data.size());
    memcpy(out,&state.data[0],state.data.size());
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
    return "8-bit state indices, with full 8bit dense value matrix without AVX";
}

bool ignoreOutput(){return false;}
