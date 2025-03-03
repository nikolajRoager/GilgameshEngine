
#pragma once
// A header which includes AVX on all platforms
// Also includes a function for testing availability
// Created by nikolaj on 28/02/25.
//

#ifdef _WIN32
#include <intrin.h>

inline int getAVXSupport() {
    //MSVC compiler
    int cpuInfo[4];
    __cpuid(cpuInfo, 0);

    if (int nIds = cpuInfo[0]; nIds >= 7) {
        __cpuid(cpuInfo, 7);
        if ((cpuInfo[1] & (1 << 16)) != 0)// Check bit 16 of EBX for AVX-512 support
            return 2;//AVX-512, we have at least 512 bits (supercedes AVX2)
        else if ((cpuInfo[1] & (1 << 5)) != 0)// Check bit 5 of EBX for AVX2 support
            return 1;//AVX2 We have at least 256 bits
        else//This CPU only supports standard AVX or below, that is NOT enough
            return 0;
    }
    return 0;//Oh ... that can't be good, AVX2 certainly couldn't be detected
}

#else
#include <immintrin.h>
/// @brief AI generated code (with Human generated comments) to detect if AVX 2 is supported on Windows
/// @return 2 if AVX-512 is supported (512 bits or more SIMD), 1 if only AVX2 is supported (256 or more bits), 0 if AVX2 is not found (Less than 256 bits, can not be used here)
inline int getAVXSupport() {
    //GCC compiler
    return __builtin_cpu_supports("avx512f") ? 2 : (__builtin_cpu_supports("avx2") ? 1 : 0);
}
#endif

///@brief print AVX register bits as an integer
template <typename T, typename = std::enable_if<std::is_integral_v<T>> >
inline std::string printInts(__m256i* data_ptr)
{
    //Extract and sum up the result
    T res[32/sizeof(T)];
    _mm256_storeu_si256((__m256i*)res, *data_ptr);
    std::string out="";
    for (int i = 0; i < (32/sizeof (T)); ++i)
    {
        if (i!=0)
            out+=" ";
        out+=std::to_string(res[i]);
    }
    return out;
}
