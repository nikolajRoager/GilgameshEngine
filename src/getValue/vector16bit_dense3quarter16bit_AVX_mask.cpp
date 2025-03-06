//
//
//

#include <cstdint>
#include <tuple>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <valueMatrix_dense_3of4_backformat.h>

#include "stateIndices.h"
#include "valueMatrix_dense_full.h"
#include "getValue.h"
#include "stateVector.h"
#include "stateVector_backformat.h"
#include "AVX_functions.h"

///@brief Instead of using multiplications, use a mask for all the pieces on the board (which are 0 or 1)
int32_t getValue(const void* state_ptr,const void* matrix_ptr)
{
    const auto* state = static_cast<const int16_t*>(state_ptr);
    const auto* matrix= static_cast<const int16_t*>(matrix_ptr);

    //Marking a variable as volatile prevents the compiler from optimizing it away, otherwise the compiler might remove the for-loop over all repeats
    volatile int result = 0;

    //Just something 0, can be declared constant
    const __m256i Zero = _mm256_setzero_si256();

    //First half of the state vector, contains a mask for whether player 0 has a piece in position 1 to E, and whether player 1 has a piece at 1 or 2.
    __m256i first_vec_mask = _mm256_loadu_si256((__m256i*)&state[0]);
    //Second half of the state vector, contains a mask for the last 12 positions on the board of player 1, and the number of unstarted/finished pieces as a 16 bit number
    __m256i second_vec_mask = _mm256_loadu_si256((__m256i*)&state[16]);

    first_vec_mask= _mm256_cmpgt_epi16(first_vec_mask,Zero);
    second_vec_mask= _mm256_cmpgt_epi16(second_vec_mask,Zero);

    //We will add parts of the sum as 16 bit snippets to this register, then sum it up when they are all there
    __m256i sum = _mm256_setzero_si256();//Start empty


    //The first 16 rows: here we only need 1 register per row, and we mask instead of multiplying, since the states are only 0 or 1
   for (int i = 0; i < 16; ++i)
    {
        //Equivalent to multiplying with V[i] on the entire row, but much, much faster
        if (state[i]==0)
            continue;

        //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes
        {
            __m256i m_vec = _mm256_loadu_si256((__m256i*)&matrix[i * 16 + 0]);
            //Then use the mask to blot out anything else, that is way cheaper than multiplying
            __m256i prod  = _mm256_and_si256(first_vec_mask, m_vec);
            //Add it together, don't worry it will not overflow (as long as the matrix does not contain anything larger than 8 bit integers)
            sum = _mm256_add_epi16(sum, prod);
        }
    }

    //Next 12 rows take up 2 registers, but can still be masked (ok, technically the last 4 rows should be multiplied, but they are all 0 anyway, so nevermind)
    for (int i = 16; i < 28; ++i)
    {
        //Equivalent to multiplying with V[i] on the entire row, but much, much faster
        if (state[i]==0)
            continue;

        {//first 16 columns
            __m256i m_vec = _mm256_loadu_si256((__m256i*)&matrix[i * 32 -16*16]);
            //Then use the mask to blot out anything else, that is way cheaper than multiplying
            __m256i prod  = _mm256_and_si256(first_vec_mask, m_vec);
            //Add it together, don't worry it will not overflow (as long as the matrix does not contain anything larger than 8 bit integers)
            sum = _mm256_add_epi16(sum, prod);
        }
        {//Next 16 columns
            __m256i m_vec = _mm256_loadu_si256((__m256i*)&matrix[i * 32+16-16*16]);
            //Then use the mask to blot out anything else, that is way cheaper than multiplying
            __m256i prod  = _mm256_and_si256(second_vec_mask, m_vec);
            //Add it together, don't worry it will not overflow (as long as the matrix does not contain anything larger than 8 bit integers)
            sum = _mm256_add_epi16(sum, prod);
        }
    }


    //Now take the 4 last, where we need to multiply
    for (int i = 28; i < 32; ++i)
    {
        //Equivalent to multiplying with V[i] on the entire row, but much, much faster
        if (state[i]==0)
            continue;
        __m256i vec = _mm256_setzero_si256();
        //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes
        //We need two registers to fit the entire row, originally I used a for-loop, but manually unrolling it made the code slightly faster
        {
            //Pick out a section of the vector and this row
            __m256i v_vec = _mm256_loadu_si256((__m256i*)&state[0]);
            __m256i m_vec = _mm256_loadu_si256((__m256i*)&matrix[i * 32 - 16 * 16]);
            //Multiply together, mullo only calculates the first 16 bits of the result, that is fine, we will not overflow (v contains at most 7, and the matrices shouldn't contain anything above 127)
            __m256i prod  = _mm256_mullo_epi16 (v_vec, m_vec);
            //Add it together,
            vec = _mm256_add_epi16(vec, prod);
        }
        {
            //Pick out a section of the vector and this row
            __m256i v_vec = _mm256_loadu_si256((__m256i*)&state[16]);
            __m256i m_vec = _mm256_loadu_si256((__m256i*)&matrix[i * 32 + 16 - 16 * 16]);
            //Multiply together
            __m256i prod  = _mm256_mullo_epi16 (v_vec, m_vec);
            //Add it together,
            vec = _mm256_add_epi16(vec, prod);
        }

        //Multiply with the corresponding element in V (from the row-vector on the left)
        __m256i v_elem = _mm256_set1_epi16(state[i]);
        vec = _mm256_mullo_epi16(vec, v_elem);

        //Add to the sum
        sum = _mm256_add_epi16(sum, vec);
    }

    //So far, sum contains 16 16-bit elements which sum up to the result
    //We need to convert these numbers to 32 bits before summing up, and there is one convenient instruction which does this: madd (multiplication), which adds adjacent pairs, multiplies with something (which might as well be 1) and converts the result to 32 bit
    //It is an expensive instruction ... but a single one of these is still a rather fast thing
    __m256i ones = _mm256_set1_epi16(1);
    sum = _mm256_madd_epi16(sum, ones); // Produces 8 int32_t sums

    //Then add up the rest, after some trial and error, I think this is the fastest way of doing this:
    //Make it a 128 bit register
    __m128i sum128_low = _mm256_extracti128_si256(sum, 0);
    __m128i sum128_high = _mm256_extracti128_si256(sum, 1);
    __m128i sum128 = _mm_add_epi32(sum128_low, sum128_high);

    //hadd twice, now everything is at the start bits
    sum128 = _mm_hadd_epi32(sum128, sum128);
    sum128 = _mm_hadd_epi32(sum128, sum128);

    //read it
    return _mm_cvtsi128_si32(sum128);


}

void* loadStateWorkspace(const stateIndices<int8_t>& state)
{
    auto newState = stateVector_backformat<int16_t>(state);

    //Now copy that into a new address so it won't get freed
    void* out = malloc(sizeof (int16_t)*newState.data.size());
    memcpy(out,&(newState.data[0]),sizeof (int16_t)*newState.data.size());
    return out;
}

///@brief Convert the default matrix  format to a pointer to the data-start in the format we want to use (Polymorphism is bad for performance)
void* loadMatrixWorkspace(const valueMatrix_dense_full<int8_t>& matrix)
{
    auto newMatrix= valueMatrix_dense_3of4_backformat<int16_t>(matrix);
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
    return "16-bit state vector, with 3 quarters 16bit dense value matrix with masks in AVX";
}

bool ignoreOutput() {return false;}