//
// Created by nikolaj on 23/02/25.
//
// Version which uses 8 bit state indices for state, 8bit dense full value matrix in default format
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <tuple>
#include <string>
#include "stateIndices.h"
#include "valueMatrix8bit_dense_full.h"
#include "getValue.h"

///@brief The best I can do, without using AVX: Use state indices to look up matching values in the matrix. For loops have been manually unrolled (very fast, but ugly code)
int32_t getValue(const void* state_ptr,const void* matrix_ptr)
{
    //We ASSUME the state and matrix data has been initialized correctly
    const auto* state = static_cast<const int8_t*>(state_ptr);
    const auto* matrix= static_cast<const int8_t*>(matrix_ptr);
    int sum = 0;

    //Loop through the 14 indices representing the 7 pieces of either player
    sum += matrix[(state[1]) * 32 + state[1]];
    sum += matrix[(state[1]) * 32 + state[2]];
    sum += matrix[(state[1]) * 32 + state[3]];
    sum += matrix[(state[1]) * 32 + state[4]];
    sum += matrix[(state[1]) * 32 + state[5]];
    sum += matrix[(state[1]) * 32 + state[6]];
    sum += matrix[(state[1]) * 32 + state[7]];
    //add 16, to other player positions
    sum += matrix[(state[1]) * 32 + state[9]+16];
    sum += matrix[(state[1]) * 32 + state[10]+16];
    sum += matrix[(state[1]) * 32 + state[11]+16];
    sum += matrix[(state[1]) * 32 + state[12]+16];
    sum += matrix[(state[1]) * 32 + state[13]+16];
    sum += matrix[(state[1]) * 32 + state[14]+16];
    sum += matrix[(state[1]) * 32 + state[15]+16];
    sum += matrix[(state[2]) * 32 + state[1]];
    sum += matrix[(state[2]) * 32 + state[2]];
    sum += matrix[(state[2]) * 32 + state[3]];
    sum += matrix[(state[2]) * 32 + state[4]];
    sum += matrix[(state[2]) * 32 + state[5]];
    sum += matrix[(state[2]) * 32 + state[6]];
    sum += matrix[(state[2]) * 32 + state[7]];
    sum += matrix[(state[2]) * 32 + state[9]+16];
    sum += matrix[(state[2]) * 32 + state[10]+16];
    sum += matrix[(state[2]) * 32 + state[11]+16];
    sum += matrix[(state[2]) * 32 + state[12]+16];
    sum += matrix[(state[2]) * 32 + state[13]+16];
    sum += matrix[(state[2]) * 32 + state[14]+16];
    sum += matrix[(state[2]) * 32 + state[15]+16];
    sum += matrix[(state[3]) * 32 + state[1]];
    sum += matrix[(state[3]) * 32 + state[2]];
    sum += matrix[(state[3]) * 32 + state[3]];
    sum += matrix[(state[3]) * 32 + state[4]];
    sum += matrix[(state[3]) * 32 + state[5]];
    sum += matrix[(state[3]) * 32 + state[6]];
    sum += matrix[(state[3]) * 32 + state[7]];
    sum += matrix[(state[3]) * 32 + state[9]+16];
    sum += matrix[(state[3]) * 32 + state[10]+16];
    sum += matrix[(state[3]) * 32 + state[11]+16];
    sum += matrix[(state[3]) * 32 + state[12]+16];
    sum += matrix[(state[3]) * 32 + state[13]+16];
    sum += matrix[(state[3]) * 32 + state[14]+16];
    sum += matrix[(state[3]) * 32 + state[15]+16];
    sum += matrix[(state[4]) * 32 + state[1]];
    sum += matrix[(state[4]) * 32 + state[2]];
    sum += matrix[(state[4]) * 32 + state[3]];
    sum += matrix[(state[4]) * 32 + state[4]];
    sum += matrix[(state[4]) * 32 + state[5]];
    sum += matrix[(state[4]) * 32 + state[6]];
    sum += matrix[(state[4]) * 32 + state[7]];
    sum += matrix[(state[4]) * 32 + state[9]+16];
    sum += matrix[(state[4]) * 32 + state[10]+16];
    sum += matrix[(state[4]) * 32 + state[11]+16];
    sum += matrix[(state[4]) * 32 + state[12]+16];
    sum += matrix[(state[4]) * 32 + state[13]+16];
    sum += matrix[(state[4]) * 32 + state[14]+16];
    sum += matrix[(state[4]) * 32 + state[15]+16];
    sum += matrix[(state[5]) * 32 + state[1]];
    sum += matrix[(state[5]) * 32 + state[2]];
    sum += matrix[(state[5]) * 32 + state[3]];
    sum += matrix[(state[5]) * 32 + state[4]];
    sum += matrix[(state[5]) * 32 + state[5]];
    sum += matrix[(state[5]) * 32 + state[6]];
    sum += matrix[(state[5]) * 32 + state[7]];
    sum += matrix[(state[5]) * 32 + state[9]+16];
    sum += matrix[(state[5]) * 32 + state[10]+16];
    sum += matrix[(state[5]) * 32 + state[11]+16];
    sum += matrix[(state[5]) * 32 + state[12]+16];
    sum += matrix[(state[5]) * 32 + state[13]+16];
    sum += matrix[(state[5]) * 32 + state[14]+16];
    sum += matrix[(state[5]) * 32 + state[15]+16];
    sum += matrix[(state[6]) * 32 + state[1]];
    sum += matrix[(state[6]) * 32 + state[2]];
    sum += matrix[(state[6]) * 32 + state[3]];
    sum += matrix[(state[6]) * 32 + state[4]];
    sum += matrix[(state[6]) * 32 + state[5]];
    sum += matrix[(state[6]) * 32 + state[6]];
    sum += matrix[(state[6]) * 32 + state[7]];
    sum += matrix[(state[6]) * 32 + state[9]+16];
    sum += matrix[(state[6]) * 32 + state[10]+16];
    sum += matrix[(state[6]) * 32 + state[11]+16];
    sum += matrix[(state[6]) * 32 + state[12]+16];
    sum += matrix[(state[6]) * 32 + state[13]+16];
    sum += matrix[(state[6]) * 32 + state[14]+16];
    sum += matrix[(state[6]) * 32 + state[15]+16];
    sum += matrix[(state[7]) * 32 + state[1]];
    sum += matrix[(state[7]) * 32 + state[2]];
    sum += matrix[(state[7]) * 32 + state[3]];
    sum += matrix[(state[7]) * 32 + state[4]];
    sum += matrix[(state[7]) * 32 + state[5]];
    sum += matrix[(state[7]) * 32 + state[6]];
    sum += matrix[(state[7]) * 32 + state[7]];
    sum += matrix[(state[7]) * 32 + state[9]+16];
    sum += matrix[(state[7]) * 32 + state[10]+16];
    sum += matrix[(state[7]) * 32 + state[11]+16];
    sum += matrix[(state[7]) * 32 + state[12]+16];
    sum += matrix[(state[7]) * 32 + state[13]+16];
    sum += matrix[(state[7]) * 32 + state[14]+16];
    sum += matrix[(state[7]) * 32 + state[15]+16];
    sum += matrix[(state[9]+16) * 32 + state[1]];
    sum += matrix[(state[9]+16) * 32 + state[2]];
    sum += matrix[(state[9]+16) * 32 + state[3]];
    sum += matrix[(state[9]+16) * 32 + state[4]];
    sum += matrix[(state[9]+16) * 32 + state[5]];
    sum += matrix[(state[9]+16) * 32 + state[6]];
    sum += matrix[(state[9]+16) * 32 + state[7]];
    sum += matrix[(state[9]+16) * 32 + state[9]+16];
    sum += matrix[(state[9]+16) * 32 + state[10]+16];
    sum += matrix[(state[9]+16) * 32 + state[11]+16];
    sum += matrix[(state[9]+16) * 32 + state[12]+16];
    sum += matrix[(state[9]+16) * 32 + state[13]+16];
    sum += matrix[(state[9]+16) * 32 + state[14]+16];
    sum += matrix[(state[9]+16) * 32 + state[15]+16];
    sum += matrix[(state[10]+16) * 32 + state[1]];
    sum += matrix[(state[10]+16) * 32 + state[2]];
    sum += matrix[(state[10]+16) * 32 + state[3]];
    sum += matrix[(state[10]+16) * 32 + state[4]];
    sum += matrix[(state[10]+16) * 32 + state[5]];
    sum += matrix[(state[10]+16) * 32 + state[6]];
    sum += matrix[(state[10]+16) * 32 + state[7]];
    sum += matrix[(state[10]+16) * 32 + state[9]+16];
    sum += matrix[(state[10]+16) * 32 + state[10]+16];
    sum += matrix[(state[10]+16) * 32 + state[11]+16];
    sum += matrix[(state[10]+16) * 32 + state[12]+16];
    sum += matrix[(state[10]+16) * 32 + state[13]+16];
    sum += matrix[(state[10]+16) * 32 + state[14]+16];
    sum += matrix[(state[10]+16) * 32 + state[15]+16];
    sum += matrix[(state[11]+16) * 32 + state[1]];
    sum += matrix[(state[11]+16) * 32 + state[2]];
    sum += matrix[(state[11]+16) * 32 + state[3]];
    sum += matrix[(state[11]+16) * 32 + state[4]];
    sum += matrix[(state[11]+16) * 32 + state[5]];
    sum += matrix[(state[11]+16) * 32 + state[6]];
    sum += matrix[(state[11]+16) * 32 + state[7]];
    sum += matrix[(state[11]+16) * 32 + state[9]+16];
    sum += matrix[(state[11]+16) * 32 + state[10]+16];
    sum += matrix[(state[11]+16) * 32 + state[11]+16];
    sum += matrix[(state[11]+16) * 32 + state[12]+16];
    sum += matrix[(state[11]+16) * 32 + state[13]+16];
    sum += matrix[(state[11]+16) * 32 + state[14]+16];
    sum += matrix[(state[11]+16) * 32 + state[15]+16];
    sum += matrix[(state[12]+16) * 32 + state[1]];
    sum += matrix[(state[12]+16) * 32 + state[2]];
    sum += matrix[(state[12]+16) * 32 + state[3]];
    sum += matrix[(state[12]+16) * 32 + state[4]];
    sum += matrix[(state[12]+16) * 32 + state[5]];
    sum += matrix[(state[12]+16) * 32 + state[6]];
    sum += matrix[(state[12]+16) * 32 + state[7]];
    sum += matrix[(state[12]+16) * 32 + state[9]+16];
    sum += matrix[(state[12]+16) * 32 + state[10]+16];
    sum += matrix[(state[12]+16) * 32 + state[11]+16];
    sum += matrix[(state[12]+16) * 32 + state[12]+16];
    sum += matrix[(state[12]+16) * 32 + state[13]+16];
    sum += matrix[(state[12]+16) * 32 + state[14]+16];
    sum += matrix[(state[12]+16) * 32 + state[15]+16];
    sum += matrix[(state[13]+16) * 32 + state[1]];
    sum += matrix[(state[13]+16) * 32 + state[2]];
    sum += matrix[(state[13]+16) * 32 + state[3]];
    sum += matrix[(state[13]+16) * 32 + state[4]];
    sum += matrix[(state[13]+16) * 32 + state[5]];
    sum += matrix[(state[13]+16) * 32 + state[6]];
    sum += matrix[(state[13]+16) * 32 + state[7]];
    sum += matrix[(state[13]+16) * 32 + state[9]+16];
    sum += matrix[(state[13]+16) * 32 + state[10]+16];
    sum += matrix[(state[13]+16) * 32 + state[11]+16];
    sum += matrix[(state[13]+16) * 32 + state[12]+16];
    sum += matrix[(state[13]+16) * 32 + state[13]+16];
    sum += matrix[(state[13]+16) * 32 + state[14]+16];
    sum += matrix[(state[13]+16) * 32 + state[15]+16];
    sum += matrix[(state[14]+16) * 32 + state[1]];
    sum += matrix[(state[14]+16) * 32 + state[2]];
    sum += matrix[(state[14]+16) * 32 + state[3]];
    sum += matrix[(state[14]+16) * 32 + state[4]];
    sum += matrix[(state[14]+16) * 32 + state[5]];
    sum += matrix[(state[14]+16) * 32 + state[6]];
    sum += matrix[(state[14]+16) * 32 + state[7]];
    sum += matrix[(state[14]+16) * 32 + state[9]+16];
    sum += matrix[(state[14]+16) * 32 + state[10]+16];
    sum += matrix[(state[14]+16) * 32 + state[11]+16];
    sum += matrix[(state[14]+16) * 32 + state[12]+16];
    sum += matrix[(state[14]+16) * 32 + state[13]+16];
    sum += matrix[(state[14]+16) * 32 + state[14]+16];
    sum += matrix[(state[14]+16) * 32 + state[15]+16];
    sum += matrix[(state[15]+16) * 32 + state[1]];
    sum += matrix[(state[15]+16) * 32 + state[2]];
    sum += matrix[(state[15]+16) * 32 + state[3]];
    sum += matrix[(state[15]+16) * 32 + state[4]];
    sum += matrix[(state[15]+16) * 32 + state[5]];
    sum += matrix[(state[15]+16) * 32 + state[6]];
    sum += matrix[(state[15]+16) * 32 + state[7]];
    sum += matrix[(state[15]+16) * 32 + state[9]+16];
    sum += matrix[(state[15]+16) * 32 + state[10]+16];
    sum += matrix[(state[15]+16) * 32 + state[11]+16];
    sum += matrix[(state[15]+16) * 32 + state[12]+16];
    sum += matrix[(state[15]+16) * 32 + state[13]+16];
    sum += matrix[(state[15]+16) * 32 + state[14]+16];
    sum += matrix[(state[15]+16) * 32 + state[15]+16];
    return static_cast<int16_t>(sum);
}
///@brief Convert the default matrix  format to a pointer to the data-start in the format we want to use (Polymorphism is bad for performance)
void* loadMatrixWorkspace(const valueMatrix8bit_dense_full& matrix)
{
    //just copy the data and return it
    auto out = malloc(matrix.size());
    memcpy(out,matrix.data(),matrix.size());
    return out;
}

///@brief Free the workspace used for this algorithm, assuming we have loaded it
void freeWorkspace(void* stateAddress, void* matrixAddress)
{
    free(stateAddress);
    free(matrixAddress);
}

void* loadStateWorkspace(const stateIndices<int8_t>& state)
{
    //just copy the data and return it
    auto out = malloc(state.data.size());
    memcpy(out,&state.data[0],state.data.size());
    return out;
}
///@brief for displaying what algorithm we are testing
std::string algorithmDescription()
{
    return "8-bit state indices, with full 8bit dense value matrix with manually unrolled for-loopswithout AVX";
}

bool ignoreOutput(){return false;}
