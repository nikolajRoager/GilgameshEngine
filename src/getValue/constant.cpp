// Created by nikolaj on 22/02/25.
//
// DOES NOT GIVE THE CORRECT VALUE! Used as a baseline for the speed test, by just returning 0



#include <cstdint>
#include <tuple>
#include "stateIndices8bit.h"
#include "valueMatrix8bit_dense_full.h"
#include "getValue.h"

///@brief DOES NOT GIVE A CORRECT RESULT, LITERALLY JUST RETURNS 0, Used this as a baseline for the speed-test
int16_t getValue(stateIndices8bit state, valueMatrix8bit_dense_full matrix)
{
    return 0;
}
