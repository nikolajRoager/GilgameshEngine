#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>
#include <cstdint>

//Various SIMD functions, works with AVX2
#include <immintrin.h>

//Windows intrinsics, such as __cpuid
//#include <intrin.h>

#define UNROLL_INDEXING

using std::cout;
using std::endl;
using std::vector;

#define cols 32
#define HalfCols 16
//All 16 bits set to 1
#define MaxInt16 (int16_t)0b1111111111111111


void stateIndex_32by32_matrix()
{
    int8_t Matrix[]=
       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    //Example state
    int8_t state[]={ 0, 0, 1, 6,10,14,15, 0+16, 2+16, 4+16,10+16,13+16,15+16,15+16};



    auto Then= std::chrono::system_clock::now();
    int Repeats = 100000;
    //Marking a variable as volatile prevents the compiler from optimizing it away, otherwise the compiler might see a for-loop which does nothing and delete it
    volatile int sum = 0;
    for (int repeat = 0; repeat<Repeats; ++repeat)
    {
        sum = 0;
        for (int p0 : state)
            for (int p1 : state)
            {
                sum+=Matrix[p0*cols+p1];
            }

    }
    auto Now = std::chrono::system_clock::now();
    cout<<"Got "<<sum<<endl;
    cout<<"Done in "<<double(std::chrono::duration_cast<std::chrono::nanoseconds>(Now-Then).count())/Repeats<<" ns"<<endl;
}

void simd_piecelist()
{
    int8_t Matrix[]=
       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    //The state includes a bunch of 0xFF, they are unused, and only included to prevent us from loading Junk data, they get turned into 0's by the shuffle function
    int8_t state[] = {0, 0, 1, 6,10,14,15,//First state
                      (int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,//Unused, will be zeroed
                      0, 2, 4,10,13,15,15,//Second state
                      (int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,/*Unused, will be zeroed*/};

    auto Then= std::chrono::system_clock::now();
    int Repeats = 100000;
    //Marking a variable as volatile prevents the compiler from optimizing it away, otherwise the compiler might see a for-loop which does nothing and delete it
    volatile int sum = 0;
    for (int repeat = 0; repeat<Repeats; ++repeat)
    {

        //Load the state into a register, it is exactly 256 bits
        __m256i state_vec = _mm256_loadu_si256((__m256i*)&state[0]);
        __m256i sum_vec = _mm256_setzero_si256();//Somewhere to put our sum, will be a list of 16 bit numbers, which we shall sum up later
        sum = 0;

        //Loop through the state, both the 7 of the first player, and the 7 of the latter player
        //The below code uses a for-loop, and is more readable, below that I have MANUALLY unrolled the for-loop for speed
        //It is somewhat better commented than the manually unrolled code below that
       #ifndef UNROLL_INDEXING
        for (int pid =0; pid <2; ++pid)
            for (int i =0; i<7; ++i)
            {
                //The ID of the row corresponding to this location
                int p0 = pid*16+state[pid*16+i];

                //Now we could simply loop though state again, and add everything to the sum like this:
                //int integer_sum=0;
                //for (int _pid =0; _pid <2; ++_pid)
                //    for (int j =0; j<7; ++j)
                //        integer_sum+=Matrix[p0*cols+_pid*16+state[_pid*16+j]];

                //But we can also use 8 or 5 SIMD instructions
                //Load data from this row in the matrix
                __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

                //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
                //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
                //The 0xFF elements are interpreted as unset, and are set to 0
                //None of this is undefined behavior!!!
                __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

                //Convert either end to 16 bit to avoid overflow, then HADD up
                __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

                sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);

                //Only the lower half of the matrix has anything in the high bits, we can save 3 instructions by skipping this
                if (pid==1)
                {
                    __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,1));
                    sum_vec = _mm256_add_epi16(high16bitRow, sum_vec);
                }
            }
        #else
        //Manually unrolled, copy pasted code, the comments are repeated
        {//index 0 of player 0
            //The ID of the row corresponding to this location
            const int p0 = state[0];
            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
        }
        {//index 1 of player 0
            //The ID of the row corresponding to this location
            const int p0 = state[1];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
        }
        {//index 2 of player 0
            //The ID of the row corresponding to this location
            const int p0 = state[2];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
        }
        {//index 3 of player 0
            //The ID of the row corresponding to this location
            const int p0 = state[3];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
        }
        {//index 4 of player 0
            //The ID of the row corresponding to this location
            const int p0 = state[4];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
        }
        {//index 5 of player 0
            //The ID of the row corresponding to this location
            const int p0 = state[5];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
        }
        {//index 6 of player 0
            //The ID of the row corresponding to this location
            const int p0 = state[6];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
        }
        //Manually unrolled, copy pasted code, the comments are repeated
        {//index 0 of player 1
            //The ID of the row corresponding to this location
            const int p0 = 16+state[16];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);

            {
                __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,1));
                sum_vec = _mm256_add_epi16(high16bitRow, sum_vec);
            }
        }
        {//index 1 of player 1
            //The ID of the row corresponding to this location
            const int p0 = 16+state[17];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
            {
                __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,1));
                sum_vec = _mm256_add_epi16(high16bitRow, sum_vec);
            }
        }
        {//index 2 of player 1
            //The ID of the row corresponding to this location
            const int p0 = 16+state[18];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
            {
                __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,1));
                sum_vec = _mm256_add_epi16(high16bitRow, sum_vec);
            }

        }
        {//index 3 of player 1
            //The ID of the row corresponding to this location
            const int p0 = 16+state[19];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
            {
                __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,1));
                sum_vec = _mm256_add_epi16(high16bitRow, sum_vec);
            }
        }
        {//index 4 of player 1
            //The ID of the row corresponding to this location
            const int p0 = 16+state[20];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
            {
                __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,1));
                sum_vec = _mm256_add_epi16(high16bitRow, sum_vec);
            }
        }
        {//index 5 of player 1
            //The ID of the row corresponding to this location
            const int p0 = 16+state[21];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
            {
                __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,1));
                sum_vec = _mm256_add_epi16(high16bitRow, sum_vec);
            }
        }
        {//index 6 of player 1
            //The ID of the row corresponding to this location
            const int p0 = 16+state[22];

            //Load data from this row in the matrix
            __m256i row = _mm256_loadu_si256((__m256i*)&Matrix[p0*cols]);

            //Pick out the indexed matrix elements, and put them at the start of the matrix, this single instruction replaces the 14 in the for-loop
            //The second state goes after the 16 byte mark, hence in the second 128 bit lane, it thus indexes the matrix from the middle, not the start (which is what we want)
            //The 0xFF elements are interpreted as unset, and are set to 0
            //None of this is undefined behavior!!!
            __m256i indexedElements = _mm256_shuffle_epi8(row, state_vec);

            //Convert either end to 16 bit to avoid overflow, then HADD up
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,0));

            sum_vec = _mm256_add_epi16(low16bitRow, sum_vec);
            {
                __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(indexedElements,1));
                sum_vec = _mm256_add_epi16(high16bitRow, sum_vec);
            }
        }
        #endif

        //Trial and error suggests the using SIMD to add up the numbers in sum_vec is NOT FASTER
        //I both tried using hadd, or extracting two _m128i's from sum_vec and adding them up, the result was slower
        //I know for a FACT that the data is concentrated in the first 7 bytes
        int16_t final_data[16];
        _mm256_storeu_si256((__m256i*)&final_data[0], sum_vec);
        sum = final_data[0]+final_data[1]+final_data[2]+final_data[3]+final_data[4]+final_data[5]+final_data[6]+final_data[7];

    }
    auto Now = std::chrono::system_clock::now();
    cout<<"Got "<<sum<<endl;
    cout<<"Done in "<<double(std::chrono::duration_cast<std::chrono::nanoseconds>(Now-Then).count())/Repeats<<" ns"<<endl;
}


void noavx_statevector()
{
    vector<char> Matrix(cols*cols,0);

    Matrix=
       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    //Example state
    uint16_t V[]=
      {2, 1,0,0,0,0,1,0,0,0,1,0,0,0,1, 1,
       1, 0,1,0,1,0,0,0,0,0,1,0,0,1,0, 2};

    auto Then= std::chrono::system_clock::now();
    int Repeats = 100000;
    //Marking a variable as volatile prevents the compiler from optimizing it away, otherwise the compiler might see a for-loop which does nothing and delete it, which would ruin our tests
    volatile int sum = 0;
    for (int repeat = 0; repeat<Repeats; ++repeat)
    {
        sum = 0;

        for (int i = 0; i < cols; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (V[i]!=0 && V[j]!=0)
                    sum+=Matrix[i+j*cols]*V[i]*V[j];
            }
        }
    }
    auto Now = std::chrono::system_clock::now();
    cout<<"Got "<<sum<<endl;
    cout<<"Done in "<<double(std::chrono::duration_cast<std::chrono::nanoseconds>(Now-Then).count())/Repeats<<" ns"<<endl;
}

    void simd_statevector_16bit()
{
    //I am assuming 256 bit registers from AVX2
    //To avoid casting, I use int16_t for the matrix and vector
    //Test data to upload
    uint16_t M[]=
       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    //Example state vector
    uint16_t V[]=
      {2, 1,0,0,0,0,1,0,0,0,1,0,0,0,1, 1,
       1, 0,1,0,1,0,0,0,0,0,1,0,0,1,0, 2};

    auto Then= std::chrono::system_clock::now();
    int Repeats = 100000;
    //Marking a variable as volatile prevents the compiler from optimizing it away, otherwise the compiler might see a for-loop which does nothing and delete it
    volatile int result = 0;

    for (int repeat = 0; repeat<Repeats; ++repeat)
    {
        //We will add parts of the sum as 16 bit snippets to this register, then sum it up when they are all there
        __m256i sum = _mm256_setzero_si256();//Start empty

        //For every row in the matrix (it is square, so it is equal to cols)
        for (int i = 0; i < cols; ++i)
        {
            __m256i vec = _mm256_setzero_si256();

            //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes
            for (int j = 0; j < cols; j += 16)
            {
                //Pick out a section of the vector and this row
                __m256i v_vec = _mm256_loadu_si256((__m256i*)&V[j]);
                __m256i m_vec = _mm256_loadu_si256((__m256i*)&M[i * cols + j]);

                //Multiply them together
                __m256i prod  = _mm256_madd_epi16 (v_vec, m_vec);

                //Add it together,
                vec = _mm256_add_epi16(vec, prod);
            }

            //Multiply with the corresponding element in V (from the row-vector on the left)
            __m256i v_elem = _mm256_set1_epi16(V[i]);
            vec = _mm256_mullo_epi16(vec, v_elem);

            //Add to the sum
            sum = _mm256_add_epi16(sum, vec);
        }

        //Extract and sum up the result
        int16_t res[16];
        _mm256_storeu_si256((__m256i*)res, sum);
        result = res[0] + res[1] + res[2] + res[3] + res[4] + res[5] + res[6] + res[7]+ res[8] + res[9] + res[10] + res[11] + res[12] + res[13] + res[14] + res[15];
    }
    auto Now = std::chrono::system_clock::now();
    cout<<"Got "<<result<<std::endl;
    cout<<"Done in "<<double(std::chrono::duration_cast<std::chrono::nanoseconds>(Now-Then).count())/Repeats<<" ns"<<endl;
}
/// @brief We use a mask for the pieces on the board, and treet the pieces not on the board seperately
void simd_statevector_16bit_mask()
{
    //I am assuming 256 registers bit from AVX2
    //To avoid casting, I use int16_t for the matrix and vector
    //Test data to upload
    int16_t M[]=
    //Let me tryt to explain the structure of the matrix in memory, and why it allows me to simplify many calculations
    //This works best if the lines are not wrapping around
       {

//The first 14 columns are selected if player 0 has a piece in position #
//    # 1 2 3 4 5 6 7 8 9 A B C D E
//      | | | | | | | | | | | | | | The next are selected if player 1 is at position #
//      | | | | | | | | | | | | | |  1 2   3 4 5 6 7 8 9 A B C D E
//      | | | | | | | | | | | | | |  | |   | | | | | | | | | | | | The final 4 get multiplied by:
//      | | | | | | | | | | | | | |  | |   | | | | | | | | | | | |  0 unstarted
//      | | | | | | | | | | | | | |  | |   | | | | | | | | | | | |  | 0 finished
//      | | | | | | | | | | | | | |  | |   | | | | | | | | | | | |  | | 1 unstarted
//      | | | | | | | | | | | | | |  | |   | | | | | | | | | | | |  | | | 1 finished
//      Block A | | | | | | | | | | Block B| Block C | | | | | | |  Block D
//      v v v v v v v v v v v v v v  v v   v v v v v v v v v v v v  v v v v //Similarly the top 14 columns get selected, if player 0 has a piece at #
        1,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-1
        1,1,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-2
        1,1,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-3
        1,1,1,1,0,0,0,0,0,0,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-4
        1,1,1,1,1,0,0,0,0,0,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-5
        1,1,1,1,1,1,0,0,0,0,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-6
        1,1,1,1,1,1,1,0,0,0,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-7
        1,1,1,1,1,1,1,1,0,0,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-8
        1,1,1,1,1,1,1,1,1,0,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-9
        1,1,1,1,1,1,1,1,1,1,0,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-A
        1,1,1,1,1,1,1,1,1,1,1,0,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-B
        1,1,1,1,1,1,1,1,1,1,1,1,0,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-C
        1,1,1,1,1,1,1,1,1,1,1,1,1,0, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-D
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-E
        //Block E                    Block F  Block G               Block H //And these get selected if player 1 is at #
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,0,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-1
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-2
        //Block I                    Block J  Block K               Block L
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-3
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-4
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-5
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,0,0,0,0,0,0,0,0, 0,0,0,0,//<-6
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,0,0,0,0,0,0,0, 0,0,0,0,//<-7
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,0,0,0,0,0,0, 0,0,0,0,//<-8
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,0,0,0,0,0, 0,0,0,0,//<-9
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,1,0,0,0,0, 0,0,0,0,//<-A
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,1,1,0,0,0, 0,0,0,0,//<-B
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,1,1,1,0,0, 0,0,0,0,//<-C
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,1,1,1,1,0, 0,0,0,0,//<-D
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,//<-E
        //Block M                    Block O  Block P               Block Q     And the final 4 get multiplied by:
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,1,1,1,1,1, 1,0,0,0,//<-0 unstarted
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,1,1,1,1,1, 1,1,0,0,//<-0 finished
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,0,//<-1 unstarted
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,  1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,//<-1 finished

        //The most logical way to divide up the matrix, would be block A (player 0 0), Block B+Block C (plyer 0 1, which IS all 0 and can be skipped), Block E+F+I+J (Player 1 0) and Block K+L (player 1 1) and finally block M (player 0 and unstarted/finished of both) block O+P (player 1 and unstarted/finished) and finally Block Q (unstarted/finished and unstarted/finished); (Blocks D, H, and L are all 0 and need not be considered)

        //However we need 256 bit per register, so I will look at the matrix using the blocks: A+B+E+F, skip C+D+G+H, I+J, K+L, M+O, and P+Q
        };

    //Example state, this time only the pieces on the board
    uint16_t V[]=
      {1,0,0,0,0,1,0,0,0,1,0,0,0,1,
       0,1,0,1,0,0,0,0,0,1,0,0,1,0,
        2,1,1,2};/*The last four are unstarted and finished for player 0 and 1*/

    //Marking a variable as volatile prevents the compiler from optimizing it away, otherwise the compiler might remove the for-loop over all repeats
    volatile int result = 0;

    //Just something 0, can be declared constant
    const __m256i Zero = _mm256_setzero_si256();

//Uncomment to print every step of the algorithm
#define VERBOSE

    auto Then = std::chrono::high_resolution_clock::now();
    int Repeats = 10000000;
#ifdef VERBOSE
//I am sure we don't want to see everything printed 0.1 million
    Repeats=1;
#endif


    for (int repeat = 0; repeat<Repeats; ++repeat)
    {

        //First half of the state vector, contains a mask for whether or not player 0 has a piece in position 1 to E, and whether player 1 has a piece at 1 or 2.
        __m256i first_vec_mask = _mm256_loadu_si256((__m256i*)&V[0]);
        //Second half of the state vector, contains a mask for the last 12 positions on the board of player 1, and the number of unstarted/finished pieces as a 16 bit number
        __m256i second_vec_mask = _mm256_loadu_si256((__m256i*)&V[16]);

        first_vec_mask= _mm256_cmpgt_epi16(first_vec_mask,Zero);
        second_vec_mask= _mm256_cmpgt_epi16(second_vec_mask,Zero);


        //We will add parts of the sum as 16 bit snippets to this register, then sum it up when they are all there
        __m256i sum = _mm256_setzero_si256();//Start empty

        //For every row in the matrix, except the 4 last (which are special as we need to multiply them
        for (int i = 0; i < 16; ++i)
        {
            //Equivalent to multiplying with V[i] on the entire row, but much, much faster
            if (V[i]==0)
                continue;

            //A temporary vector used for storing this column
            __m256i vec = _mm256_setzero_si256();
            //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes
            {
                __m256i m_vec = _mm256_loadu_si256((__m256i*)&M[i * cols + 0]);
                //Then use the mask to blot out anything else, that is way cheaper than multiplying
                __m256i prod  = _mm256_and_si256(first_vec_mask, m_vec);
                //Add it together,
                vec = _mm256_add_epi16(vec, prod);
            }
            //Add to the sum
            sum = _mm256_add_epi16(sum, vec);
        }
        for (int i = 0; i < 12; ++i)
        {
            //Equivalent to multiplying with V[i] on the entire row, but much, much faster
            if (V[i+16]==0)
                continue;

            //A temporary vector used for storing this column
            __m256i vec = _mm256_setzero_si256();
            //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes
            {
                __m256i m_vec = _mm256_loadu_si256((__m256i*)&M[i * cols+16*cols + 0]);
                //Then use the mask to blot out anything else, that is way cheaper than multiplying
                __m256i prod  = _mm256_and_si256(first_vec_mask, m_vec);
                //Add it together,
                vec = _mm256_add_epi16(vec, prod);
            }

            //We need two registers to hold a row, but we know the top-right 16x16 submatrix is all 0, so we can skip it
            __m256i m_vec = _mm256_loadu_si256((__m256i*)&M[i * cols + 16+16*cols]);
            //Then use the mask to blot out anything else, that is way cheaper than multiplying
            __m256i prod  = _mm256_and_si256(second_vec_mask, m_vec);
            //Add it together,
            vec = _mm256_add_epi16(vec, prod);
            //Add to the sum
            sum = _mm256_add_epi16(sum, vec);
        }
        //Now take the 4 last, where we need to multiply
        for (int i = cols-4; i < cols; ++i)
        {
            //Equivalent to multiplying with V[i] on the entire row, but much, much faster
            if (V[i]==0)
                continue;
            __m256i vec = _mm256_setzero_si256();
            //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes
            //We need two registers to fit the entire row, originally I used a for-loop, but manually unrolling it made the code slightly faster
            {
                //Pick out a section of the vector and this row
                __m256i v_vec = _mm256_loadu_si256((__m256i*)&V[0]);
                __m256i m_vec = _mm256_loadu_si256((__m256i*)&M[i * cols]);
                //Multiply them together
                __m256i prod  = _mm256_madd_epi16 (v_vec, m_vec);
                //Add it together,
                vec = _mm256_add_epi16(vec, prod);
            }
            //We are going to need two registers per row, manually unrolloing the for-loop is faster
            {
                //Pick out a section of the vector and this row
                __m256i v_vec = _mm256_loadu_si256((__m256i*)&V[16]);
                __m256i m_vec = _mm256_loadu_si256((__m256i*)&M[i * cols + 16]);
                //Multiply them together
                __m256i prod  = _mm256_madd_epi16 (v_vec, m_vec);
                //Add it together,
                vec = _mm256_add_epi16(vec, prod);
            }

            //Multiply with the corresponding element in V (from the row-vector on the left)
            __m256i v_elem = _mm256_set1_epi16(V[i]);
            vec = _mm256_mullo_epi16(vec, v_elem);

            //Add to the sum
            sum = _mm256_add_epi16(sum, vec);
        }
        //Extract and sum up the result
        //A single HADD seems to be the fastest
        sum=_mm256_hadd_epi16(sum,sum);
        int16_t res[16];
        _mm256_storeu_si256((__m256i*)res, sum);
        result = res[0] + res[1] + res[2] + res[3] + res[8] + res[9] + res[10] + res[11];
    }
    auto Now = std::chrono::system_clock::now();
    cout<<"Got "<<result<<std::endl;
    cout<<"Done in "<<double(std::chrono::duration_cast<std::chrono::nanoseconds>(Now-Then).count())/Repeats<<" n "<<endl;
}



/// @brief INFERIOR SPEED We use a mask for the pieces on the board, and treet the pieces not on the board seperately, the matrix and state vectors are 8bit, the superior data-storage is completely offset by the inferior speed
void simd_statevector_8bit_mask()
{
    //I am assuming 256 registers bit from AVX2
    //To avoid casting, I use int16_t for the matrix and vector
    //Test data to upload
    int8_t M[]=
    //The last 4 rows and columns represent unstarted, finished of player 0, then unstarted and finished of player 1
       {
        //This chunk is only "multiplied" by 0 or 1, this can be done with a mask
        1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,//These columns are multiplied
        1,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,//by started and unstarted
        1,1,1,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,//but since they are all 0
        1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,//we don't actually do that

        1,1,1,1, 1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,

        1,1,1,1, 1,1,1,1, 1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,

        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,

        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0,  0,0,0,0,

        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,0,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 0,0,0,0,  0,0,0,0,

        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,0,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,0,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,0,  0,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,  0,0,0,0,

        //The rows below need to be multiplied by unstarted/started, AND the last columns need to be multiplied by the corrosponding number
        //Since SIMD multiplication operations are not defined for 8 bit numbers, we need to store them in 8 16 bit registers
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,  1,0,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,  1,1,0,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,  1,1,1,0,
        1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,  1,1,1,1};

    //Example state, this time only the pieces on the board
    uint8_t V[]=
      {1,0,0,0,0,1,0,0,0,1,0,0,0,1,
       0,1,0,1,0,0,0,0,0,1,0,0,1,0,
        2,1,1,2};/*The last four are unstarted and finished for player 0 and 1*/

    auto Then= std::chrono::system_clock::now();
    int Repeats = 100000;
    //Marking a variable as volatile prevents the compiler from optimizing it away, otherwise the compiler might see a for-loop which does nothing and delete it
    volatile int result = 0;

    for (int repeat = 0; repeat<Repeats; ++repeat)
    {
        //Just something 0
        __m256i Zero = _mm256_setzero_si256();
        //We will add parts of the sum as 16 bit snippets to this reguuter, then sum it up when they are all there
        __m256i sum = _mm256_setzero_si256();//Start empty

        //For every row in the matrix, except the 4 last
        for (int i = 0; i < cols-4; ++i)
        {
            //Equivalent to multiplying with V[i] on the entire row, but much, much faster
            if (V[i]==0)
                continue;
            //Compute the dot-product for the entire row, it can JUST fit into 256 bits

            //Upload data to 2 AVX2 registers
            __m256i v_vec = _mm256_loadu_si256((__m256i*)&V[0]);
            __m256i m_vec = _mm256_loadu_si256((__m256i*)&M[i * cols + 0]);

            //Turn this into a Mask of non-zero elements in V
            v_vec= _mm256_cmpgt_epi8(v_vec,Zero);
            //Then use the mask to blot out anything else, that is way cheaper than multiplying
            __m256i prod  = _mm256_and_si256(v_vec, m_vec);

            //We want to add this to the sum ... but THIS would maybe overflow:
            //sum = _mm256_add_epi8(sum, prod);

            //Add to the sum, this might overflow, so first we are going to split the bytes into the low and high half, then convert to 16 bits
            __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(prod,0));
            __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(prod,1));

            sum = _mm256_add_epi8(sum, low16bitRow);
            sum = _mm256_add_epi8(sum, high16bitRow);
        }
        //Now take the 4 last, where we need to multiply something onto it
        for (int i = cols-4; i < cols; ++i)
        {
            //Equivalent to multiplying with V[i] on the entire row, but much, much faster
            if (V[i]==0)
                continue;
            //Multiplication is DEFINITELY going to overflow 8 bits, so we split the row 2 sections with 16 16 biy numbers
            __m256i vec = _mm256_setzero_si256();
            //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes

            //Pick out a section of the vector and this entire row
            __m256i v_vec = _mm256_loadu_si256((__m256i*)&V[0]);
            __m256i m_vec = _mm256_loadu_si256((__m256i*)&M[i * cols]);
            {
                __m256i low_v=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(v_vec,0));
                __m256i low_m=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(m_vec,0));

                //For these first elements, we multiply with 0 or 1, so a mask is good enough

                //Turn this into a Mask of non-zero elements in V
                low_v= _mm256_cmpgt_epi16(low_v,Zero);
                //Then use the mask to blot out anything else, that is way cheaper than multiplying
                __m256i prod  = _mm256_and_si256(low_v, low_m);

                //Add it together,
                vec = _mm256_add_epi16(vec, prod);
            }
            //We are going to need two registers per row, manually unrolloing the for-loop is faster
            {
                __m256i high_v=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(v_vec,1));
                __m256i high_m=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(m_vec,1));

                //Multiply them together
                __m256i prod  = _mm256_madd_epi16 (high_v,high_m);
                //Add it together,
                vec = _mm256_add_epi16(vec, prod);
            }

            //Multiply with the corresponding element in V (from the row-vector on the left)
            __m256i v_elem = _mm256_set1_epi16(V[i]);
            vec = _mm256_mullo_epi16(vec, v_elem);

            //Add to the sum
            sum = _mm256_add_epi16(sum, vec);
        }
        //Extract and sum up the result
        //A single HADD seems to be the fastest
        int16_t res[16];
        _mm256_storeu_si256((__m256i*)res, sum);
        result = res[0] + res[1]  + res[2]  +  res[3] + res[4]
              + res[5]  + res[6]  + res[7]  +  res[8] + res[9]
              + res[10] + res[11] + res[12] + res[13] + res[14]
              + res[15];
    }
    auto Now = std::chrono::system_clock::now();
    cout<<"Got "<<result<<std::endl;
    cout<<"Done in "<<double(std::chrono::duration_cast<std::chrono::nanoseconds>(Now-Then).count())/Repeats<<" ns"<<endl;
}



/// @brief We use a mask for the pieces on the board, and treet the pieces not on the board seperately, the matrix and state vectors are 8bit
void simd_statevector_8bit_rearranged_mask()
{
    //I am assuming 256 registers bit from AVX2
    //To avoid casting, I use int16_t for the matrix and vector
    //Test data to upload
    int8_t M[]=
    //The last 4 rows and columns represent unstarted, finished of player 0, then unstarted and finished of player 1
       {
        //There are 4 blocks, with 4 or 2 chunks each, for a total of 14 chunks of 256 bit data, we will interleave the rows from 0 and up, and from 27 and down
        //That way each two chunks take 256 bytes, and calculating what state indices apply is exceptionally easy and quick
//The number in front is the row, the entry after the number in front is column 0, 1, 2 and so on
/*row  0*/1,0,0,0,/*row 27*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//<-Chunk  0 Block 0
/*row  1*/1,1,0,0,/*row 26*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,//<-Chunk  1 :
/*row  2*/1,1,1,0,/*row 25*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,//<-Chunk  2 :
/*row  3*/1,1,1,1,/*row 24*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,//<-Chunk  3 :
/*row  4*/1,1,1,1,1,0,0,0,/*row 23*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//<-Chunk  4 Block 0
/*row  5*/1,1,1,1,1,1,0,0,/*row 22*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,//<-Chunk  5 :
/*row  6*/1,1,1,1,1,1,1,0,/*row 21*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,//<-Chunk  6 :
/*row  7*/1,1,1,1,1,1,1,1,/*row 20*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,//<-Chunk  7 :
/*row  8*/1,1,1,1,1,1,1,1,1,0,0,0,/*row 19*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//<-Chunk  8 Block 0
/*row  9*/1,1,1,1,1,1,1,1,1,1,0,0,/*row 18*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,//<-Chunk  9 :
/*row 10*/1,1,1,1,1,1,1,1,1,1,1,0,/*row 17*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,//<-Chunk 10 :
/*row 11*/1,1,1,1,1,1,1,1,1,1,1,1,/*row 16*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,//<-Chunk 11 :
/*row 12*/1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,/*row 15*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
/*row 13*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,/*row 14*/1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        //The rows below need to be multiplied by unstarted/started, AND the last columns need to be multiplied by the corrosponding number
        //Since SIMD multiplication operations are not defined for 8 bit numbers, we need to store them in 8 16 bit registers
        //These are the chunks we will use
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1};

    //Masks corresponding to the 14 first chunks where we either mask out the first or second row, unfortunately these are too big to declare as a constant permanently loaded in the AVX2 registers
    const int8_t Masks[]=
    {//that way, if we are in chunk i, and we need to mask out the first but not the last row we need mask at (2*i+1)*32
        (int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,
        (int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,
        (int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,
        (int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0xFF,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,(int8_t)0x00,
    };

    //Example state, this time only the pieces on the board, 256 bits
    uint8_t State[]=
      {2,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,2,1,1,2};/*The last four are unstarted and finished for player 0 and 1*/
    auto Then= std::chrono::system_clock::now();
    int Repeats = 100000;
    //Marking a variable as volatile prevents the compiler from optimizing it away, otherwise the compiler might see a for-loop which does nothing and delete it
    volatile int result = 0;

    const __m256i Masks10[4] =  {_mm256_loadu_si256((__m256i*)&Masks[(0)*32]),_mm256_loadu_si256((__m256i*)&Masks[(1)*32]),_mm256_loadu_si256((__m256i*)&Masks[(2)*32]),_mm256_loadu_si256((__m256i*)&Masks[(3)*32])};

    //Just something 0
    const __m256i Zero = _mm256_setzero_si256();



    for (int repeat = 0; repeat<Repeats; ++repeat)
    {
        //For easy loading of the state, I create the 4 different possibilities ahead of time
        uint8_t V[32*4] = {0};
        std::memcpy(&V[0+00],&State[0] ,4); std::memcpy(&V[4+00] ,&State[0],28);
        std::memcpy(&V[0+32],&State[0] ,8); std::memcpy(&V[8+32] ,&State[0],24);
        std::memcpy(&V[0+64],&State[0] ,12);std::memcpy(&V[12+64],&State[0],20);
        std::memcpy(&V[0+96],&State[0] ,16);std::memcpy(&V[16+96],&State[0],16);

        //We will add parts of the sum as 16 bit snippets to this reguuter, then sum it up when they are all there
        __m256i sum = _mm256_setzero_si256();//Start empty


        for (int chunkId=0; chunkId<4;++chunkId)
        {
            //First loop through the 14 chunks, which only get multiplied by 1 or 0
            int chunkMax = chunkId*4+(chunkId==3? 2 : 4);
            int chunkStart= chunkId*4;
            for (int i =chunkStart; i< chunkMax; ++i)
            {
                //This state will be made up of the row i, followed by the row 27-i
                //the first part of the row has width (i=0,1,2,3) 4, (i=4,5,6,7) 8, (i=8,9,10,11) 12 or (12,13) 16,

                if (State[i]==0 && State[27-i]==0)
                    continue;


                //Which chunk are we in? that is which of the 4 kind of state indices should we us

                //Upload data to 2 AVX2 registers
                //This is the state multiplied from the right
                __m256i v_vec = _mm256_loadu_si256((__m256i*)&V[chunkId*32]);
                //And these are our two rows
                __m256i m_vec = _mm256_loadu_si256((__m256i*)&M[i * cols + 0]);

                //Create a mask out of the multiplication from the right
                v_vec= _mm256_cmpgt_epi8(v_vec,Zero);

                //Then use the mask to blot out anything else, that is way cheaper than multiplying
                __m256i prod  = _mm256_and_si256(v_vec, m_vec);

                //Then, if one of the two rows, making up this row is 0, mask it out
                if (State[i]==0)
                {
                    prod  = _mm256_andnot_si256(Masks10[chunkId], prod);
                }
                else if (State[27-i]==0)//Both won't be 0
                {
                    prod  = _mm256_and_si256(Masks10[chunkId], prod);
                }


/*
                int8_t res[32];
                _mm256_storeu_si256((__m256i*)res, v_vec);
                cout<<"Consider rows "<<i<<" etc. "<<endl;

                for (int8_t i : res)
                    cout<<(int)i<<' ';
                cout<<endl;
*/

                //We want to add this to the sum ... but THIS would maybe overflow:
                //sum = _mm256_add_epi8(sum, prod);

                //Add to the sum, this might overflow, so first we are going to split the bytes into the low and high half, then convert to 16 bits
                __m256i low16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(prod,0));
                __m256i high16bitRow=_mm256_cvtepi8_epi16(_mm256_extracti128_si256(prod,1));


                sum = _mm256_add_epi8(sum, low16bitRow);
                sum = _mm256_add_epi8(sum, high16bitRow);
            }
        }
        //Extract and sum up the result
        //My tests suggests the SIMD HADD instruction is NOT worth using, this is marginally faster
        int16_t res[16];
        _mm256_storeu_si256((__m256i*)res, sum);
        result = res[0] + res[1]  + res[2]  +  res[3] + res[4]
              + res[5]  + res[6]  + res[7]  +  res[8] + res[9]
              + res[10] + res[11] + res[12] + res[13] + res[14]
              + res[15];
    }
    auto Now = std::chrono::system_clock::now();
    cout<<"Got "<<result<<std::endl;
    cout<<"Done in "<<double(std::chrono::duration_cast<std::chrono::nanoseconds>(Now-Then).count())/Repeats<<" ns"<<endl;
}


/// @brief AI generated code (with Human generated comments) to detect if AVX 2 is supported on Windows
/// @return 2 if AVX-512 is supported (512 bits or more SIMD), 1 if only AVX2 is supported (256 or more bits), 0 if AVX2 is not found (Less than 256 bits, can not be used here)
int getAVXSupport() {
    //GCC compiler
    return __builtin_cpu_supports("avx512f")?2:(__builtin_cpu_supports("avx2")?1:0);
    //MSVC compiler
    /*
    int cpuInfo[4];
    __cpuid(cpuInfo, 0);
    int nIds = cpuInfo[0];

    if (nIds >= 7) {
        __cpuid(cpuInfo, 7);
        if ((cpuInfo[1] & (1 << 16)) != 0)// Check bit 16 of EBX for AVX-512 support
            return 2;//AVX-512, we have at least 512 bits (supercedes AVX2)
        else if ((cpuInfo[1] & (1 << 5)) != 0)// Check bit 5 of EBX for AVX2 support
            return 1;//AVX2 We have at least 256 bits
        else//This CPU only supports standard AVX or below, that is NOT enough
            return 0;
    }
    return 0;//Oh ... that can't be good, AVX2 certainly couldn't be detected
*/
}

int main(int, char**)
{
   cout<<"STARTING PROGRAM"<<endl;
   switch (getAVXSupport())
   {
       case 2:
           cout<<"AVX-512 supported! (but this silly little program can't take advantage os that)"<<endl;
       case 1://Fall through, AVX 512 supercedes AVX2
           cout<<"AVX2 supported! This program CAN run!"<<endl;
       break;
       default:
       case 0:
                cout<<"ERROR "<<getAVXSupport()<<", this CPU does not support AVX2 or better!!! the example will not work!"<<endl;
            return 1;
    }
    cout<<"Matrix multiplication of State Vector with for loops:"<<endl;
    noavx_statevector();
    cout<<"Matrix multiplication of State Vector with SIMD 16bit:"<<endl;
    simd_statevector_16bit();
    cout<<"\nMatrix multiplication with SIMD 16bit MASK:"<<endl;
    simd_statevector_16bit_mask();
    cout<<"\nMatrix multiplication with SIMD 8bit MASK:"<<endl;
    simd_statevector_8bit_mask();
    cout<<"\nMatrix multiplication with SIMD 8bit MASK, rearranged (Incomplete, due to inferior speed):"<<endl;
    simd_statevector_8bit_rearranged_mask();
    cout<<"\nMatrix reading with state indices:"<<endl;
    stateIndex_32by32_matrix();
    cout<<"\nMatrix reading with SIMD state indices:"<<endl;
    simd_piecelist();

return 0;
}
