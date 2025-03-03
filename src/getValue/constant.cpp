// Created by nikolaj on 22/02/25.
//
// DOES NOT GIVE THE CORRECT VALUE! Used as a baseline for the speed test, by just returning 0



#include <cstdint>
#include <tuple>
#include <cstdlib>
#include <cstring>
#include <string>
#include "stateIndices.h"
#include "valueMatrix_dense_full.h"
#include "getValue.h"

///@brief DOES NOT GIVE A CORRECT RESULT, LITERALLY JUST RETURNS 0, Used this as a baseline for the speed-test
int32_t getValue(const void* state,const void* values)
{
    return 0;
}

void* loadStateWorkspace(const stateIndices<int8_t>& state)
{
    //just copy the data and return it
    auto out = malloc(state.data.size());
    memcpy(out,&state.data[0],state.byteSize());
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
    return "constant (baseline for speedtest)";
}

bool ignoreOutput(){return true;}