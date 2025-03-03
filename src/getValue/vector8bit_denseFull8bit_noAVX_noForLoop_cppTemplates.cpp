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

///@brief Heavily inspired by User SeHe on Stackoverflow https://stackoverflow.com/a/28232338/5058424, but modified to work with a 2D matrix
template <unsigned i, unsigned j> struct unroll_lowerTriangular{
    template <typename F> static void call(F const& f)
    {
        f(i,j);
        //Next thing in this row, or go to the next row
        unroll_lowerTriangular<i-1,j>::call(f);
    }
};

///Final step
template <> struct unroll_lowerTriangular<0u,0u> {
    template <typename F> static void call(F const& f){
        f(0u,0u);
    }
};

///Go to next row
template <unsigned j> struct unroll_lowerTriangular<0u,j> {
    template <typename F> static void call(F const& f)
    {
        f(0u,j);
        unroll_lowerTriangular<j-1,j-1>::call(f);
    }
};



///@brief Matrix multiplication of 32 element vector of 8bit ints on a lower-triangular 32 by 32 matrix of 8 bit integers, using c++templates to unroll the for-loop
int32_t getValue(const void* state_ptr,const void* matrix_ptr)
{
    int sum = 0;
    const auto* state = static_cast<const int8_t*>(state_ptr);
    const auto* matrix= static_cast<const int8_t*>(matrix_ptr);
    //We loop through this "backwards" starting at 31, 31, going to 0, 31, then
    unroll_lowerTriangular<31,31>::call([&] (int i, int j){
        //This is what we repeated for every entry below the diagonal
        //Slight speed boost from not adding things which are 0
        if (state[i] && state[j])
            sum+=static_cast<int>(matrix[i+j*32])*static_cast<int>(state[i])*static_cast<int>(state[j]);
    });

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
    return "8-bit state vector, with full 8bit dense value matrix without AVX, unrolled using c++ templates";
}

bool ignoreOutput() {return false;}