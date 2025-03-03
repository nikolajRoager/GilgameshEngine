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

///@brief the conceptually simplest AVX version use 16 bit multiplications to get a 32 bit result
int32_t getValue(const void* state_ptr,const void* matrix_ptr)
{
    const auto* state = static_cast<const int16_t*>(state_ptr);
    const auto* matrix= static_cast<const int16_t*>(matrix_ptr);

    //We will add parts of the sum as 16 bit snippets to this register, then sum it up when they are all there
    __m256i sum = _mm256_setzero_si256();//Start empty


    //For every row in the matrix (it is square, so it is equal to cols)
    for (int i = 0; i < 32; ++i) {
        if (!state[i])
            continue;
        __m256i vec = _mm256_setzero_si256();

        //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes
        for (int j = 0; j < 32; j += 16) {
            //Pick out a section of the vector and this row
            __m256i v_vec = _mm256_loadu_si256((__m256i *) &state[j]);
            __m256i m_vec = _mm256_loadu_si256((__m256i *) &matrix[i * 32 + j]);

            //Multiply them together
            __m256i prod = _mm256_madd_epi16(v_vec, m_vec);

            //Add it together,
            vec = _mm256_add_epi32(vec, prod);
        }

        //Multiply with the corresponding element in V (from the row-vector on the left)
        __m256i v_elem = _mm256_set1_epi32(state[i]);
        vec = _mm256_mullo_epi32(vec, v_elem);

        //Add to the sum
        sum = _mm256_add_epi32(sum, vec);
    }

    //Extract and sum up the result, I tried using a few hadd, but it proved slower
    int32_t res[8];
    _mm256_storeu_si256((__m256i*)res, sum);
    return res[0] + res[1] + res[2] + res[3] + res[4] + res[5] + res[6] + res[7];
}

void* loadStateWorkspace(const stateIndices<int8_t>& state)
{
    auto newState = stateVector<int16_t>(state);
    //Now copy that into a new address so it won't get freed
    void* out = malloc(sizeof (int16_t)*newState.data.size());
    memcpy(out,&(newState.data[0]),sizeof (int16_t)*newState.data.size());
    return out;
}
///@brief Convert the default matrix  format to a pointer to the data-start in the format we want to use (Polymorphism is bad for performance)
void* loadMatrixWorkspace(const valueMatrix_dense_full<int8_t>& matrix)
{
    auto newMatrix= valueMatrix_dense_full<int16_t>(matrix);
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
    return "16-bit state vector, with full 16bit dense value matrix with madd AVX";
}

bool ignoreOutput() {return false;}