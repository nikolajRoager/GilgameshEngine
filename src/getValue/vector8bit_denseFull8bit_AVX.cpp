//
//
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
#include "AVX_functions.h"

///@brief AVX multiplication of 8 bit vector with the maddups instruction (which requires the state vector to be unsigned), remarkably, this is considerably slower than the 16 bit version
int32_t getValue(const void* state_ptr,const void* matrix_ptr)
{
    const auto* state = static_cast<const uint8_t*>(state_ptr);
    const auto* matrix= static_cast<const int8_t*>(matrix_ptr);

    //We will add parts of the sum as 16 bit snippets to this register, then sum it up when they are all there
    __m256i sum = _mm256_setzero_si256();//Start empty

    //For every row in the matrix (it is square, so it is equal to cols)
    for (int i = 0; i < 32; ++i) {
        if (!state[i])
            continue;
        //32 bit rows fit exactly
        //Pick out a section of the vector and this row
        __m256i v_vec = _mm256_loadu_si256((__m256i *) &state[0]);
        __m256i m_vec = _mm256_loadu_si256((__m256i *) &matrix[i * 32]);

        //Turn this into a list of signed 16-bit numbers
        __m256i prod = _mm256_maddubs_epi16(v_vec, m_vec);

        //Multiply with the corresponding element in V (from the row-vector on the left)
        __m256i v_elem = _mm256_set1_epi16(state[i]);
        //16 bit signed integers
        prod = _mm256_mullo_epi16(prod, v_elem);

        //Add to the sum
        sum = _mm256_add_epi16(sum, prod);
    }

    //Extract and sum up the result, I tried using a few hadd, but it proved slower
    int16_t res[16];
    sum=_mm256_hadd_epi16(sum,sum);
    sum=_mm256_hadd_epi16(sum,sum);
    //Using any more hadds could, hypothetically take us into overflow territory, so load and cast instead

    _mm256_storeu_si256((__m256i*)res, sum);


    return (int32_t) res[0] + (int32_t) res[1] +
            (int32_t) res[8]+(int32_t) res[9];
}

//Convert the state vector to an UNSIGNED 8 bit number
void* loadStateWorkspace(const stateIndices<int8_t>& state)
{
    auto newState = stateVector<uint8_t>(state);
    //Now copy that into a new address so it won't get freed
    void* out = malloc(sizeof (uint8_t)*newState.data.size());
    memcpy(out,&(newState.data[0]),sizeof (uint8_t)*newState.data.size());
    return out;
}
///@brief Convert the default matrix  format to a pointer to the data-start in the format we want to use (Polymorphism is bad for performance)
void* loadMatrixWorkspace(const valueMatrix_dense_full<int8_t>& matrix)
{
    auto newMatrix= valueMatrix_dense_full<int8_t>(matrix);
    auto out = malloc(newMatrix.byteSize());
    memcpy(out,newMatrix.data(),newMatrix.byteSize());
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
    return "8-bit unsigned state vector, with full 8bit signed dense value matrix with madd AVX";
}

bool ignoreOutput() {return false;}