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

///@brief Matrix multiplication of 32 element vector of 8bit ints on a lower-triangular 32 by 32 matrix of 8 bit integers, using a manually unrolled for-loop
int32_t getValue(const void* state_ptr,const void* matrix_ptr) {
    int sum = 0;
    const auto *state = static_cast<const int8_t *>(state_ptr);
    const auto *matrix = static_cast<const int8_t *>(matrix_ptr);

    //Yep, I am 100% serious (I wrote a little program to write these lines)
    if (state[0]) {
        sum += static_cast<int>(matrix[0]) * static_cast<int>(state[0]) * static_cast<int>(state[0]);
        if (state[1])
            sum += static_cast<int>(matrix[32]) * static_cast<int>(state[0]) * static_cast<int>(state[1]);
        if (state[2])
            sum += static_cast<int>(matrix[64]) * static_cast<int>(state[0]) * static_cast<int>(state[2]);
        if (state[3])
            sum += static_cast<int>(matrix[96]) * static_cast<int>(state[0]) * static_cast<int>(state[3]);
        if (state[4])
            sum += static_cast<int>(matrix[128]) * static_cast<int>(state[0]) * static_cast<int>(state[4]);
        if (state[5])
            sum += static_cast<int>(matrix[160]) * static_cast<int>(state[0]) * static_cast<int>(state[5]);
        if (state[6])
            sum += static_cast<int>(matrix[192]) * static_cast<int>(state[0]) * static_cast<int>(state[6]);
        if (state[7])
            sum += static_cast<int>(matrix[224]) * static_cast<int>(state[0]) * static_cast<int>(state[7]);
        if (state[8])
            sum += static_cast<int>(matrix[256]) * static_cast<int>(state[0]) * static_cast<int>(state[8]);
        if (state[9])
            sum += static_cast<int>(matrix[288]) * static_cast<int>(state[0]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[320]) * static_cast<int>(state[0]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[352]) * static_cast<int>(state[0]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[384]) * static_cast<int>(state[0]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[416]) * static_cast<int>(state[0]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[448]) * static_cast<int>(state[0]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[480]) * static_cast<int>(state[0]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[512]) * static_cast<int>(state[0]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[544]) * static_cast<int>(state[0]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[576]) * static_cast<int>(state[0]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[608]) * static_cast<int>(state[0]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[640]) * static_cast<int>(state[0]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[672]) * static_cast<int>(state[0]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[704]) * static_cast<int>(state[0]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[736]) * static_cast<int>(state[0]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[768]) * static_cast<int>(state[0]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[800]) * static_cast<int>(state[0]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[832]) * static_cast<int>(state[0]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[864]) * static_cast<int>(state[0]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[896]) * static_cast<int>(state[0]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[928]) * static_cast<int>(state[0]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[960]) * static_cast<int>(state[0]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[992]) * static_cast<int>(state[0]) * static_cast<int>(state[31]);
    }
    if (state[1]) {
        sum += static_cast<int>(matrix[33]) * static_cast<int>(state[1]) * static_cast<int>(state[1]);
        if (state[2])
            sum += static_cast<int>(matrix[65]) * static_cast<int>(state[1]) * static_cast<int>(state[2]);
        if (state[3])
            sum += static_cast<int>(matrix[97]) * static_cast<int>(state[1]) * static_cast<int>(state[3]);
        if (state[4])
            sum += static_cast<int>(matrix[129]) * static_cast<int>(state[1]) * static_cast<int>(state[4]);
        if (state[5])
            sum += static_cast<int>(matrix[161]) * static_cast<int>(state[1]) * static_cast<int>(state[5]);
        if (state[6])
            sum += static_cast<int>(matrix[193]) * static_cast<int>(state[1]) * static_cast<int>(state[6]);
        if (state[7])
            sum += static_cast<int>(matrix[225]) * static_cast<int>(state[1]) * static_cast<int>(state[7]);
        if (state[8])
            sum += static_cast<int>(matrix[257]) * static_cast<int>(state[1]) * static_cast<int>(state[8]);
        if (state[9])
            sum += static_cast<int>(matrix[289]) * static_cast<int>(state[1]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[321]) * static_cast<int>(state[1]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[353]) * static_cast<int>(state[1]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[385]) * static_cast<int>(state[1]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[417]) * static_cast<int>(state[1]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[449]) * static_cast<int>(state[1]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[481]) * static_cast<int>(state[1]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[513]) * static_cast<int>(state[1]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[545]) * static_cast<int>(state[1]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[577]) * static_cast<int>(state[1]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[609]) * static_cast<int>(state[1]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[641]) * static_cast<int>(state[1]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[673]) * static_cast<int>(state[1]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[705]) * static_cast<int>(state[1]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[737]) * static_cast<int>(state[1]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[769]) * static_cast<int>(state[1]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[801]) * static_cast<int>(state[1]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[833]) * static_cast<int>(state[1]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[865]) * static_cast<int>(state[1]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[897]) * static_cast<int>(state[1]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[929]) * static_cast<int>(state[1]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[961]) * static_cast<int>(state[1]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[993]) * static_cast<int>(state[1]) * static_cast<int>(state[31]);
    }if (state[2]) {
        sum += static_cast<int>(matrix[66]) * static_cast<int>(state[2]) * static_cast<int>(state[2]);
        if (state[3])
            sum += static_cast<int>(matrix[98]) * static_cast<int>(state[2]) * static_cast<int>(state[3]);
        if (state[4])
            sum += static_cast<int>(matrix[130]) * static_cast<int>(state[2]) * static_cast<int>(state[4]);
        if (state[5])
            sum += static_cast<int>(matrix[162]) * static_cast<int>(state[2]) * static_cast<int>(state[5]);
        if (state[6])
            sum += static_cast<int>(matrix[194]) * static_cast<int>(state[2]) * static_cast<int>(state[6]);
        if (state[7])
            sum += static_cast<int>(matrix[226]) * static_cast<int>(state[2]) * static_cast<int>(state[7]);
        if (state[8])
            sum += static_cast<int>(matrix[258]) * static_cast<int>(state[2]) * static_cast<int>(state[8]);
        if (state[9])
            sum += static_cast<int>(matrix[290]) * static_cast<int>(state[2]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[322]) * static_cast<int>(state[2]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[354]) * static_cast<int>(state[2]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[386]) * static_cast<int>(state[2]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[418]) * static_cast<int>(state[2]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[450]) * static_cast<int>(state[2]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[482]) * static_cast<int>(state[2]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[514]) * static_cast<int>(state[2]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[546]) * static_cast<int>(state[2]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[578]) * static_cast<int>(state[2]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[610]) * static_cast<int>(state[2]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[642]) * static_cast<int>(state[2]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[674]) * static_cast<int>(state[2]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[706]) * static_cast<int>(state[2]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[738]) * static_cast<int>(state[2]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[770]) * static_cast<int>(state[2]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[802]) * static_cast<int>(state[2]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[834]) * static_cast<int>(state[2]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[866]) * static_cast<int>(state[2]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[898]) * static_cast<int>(state[2]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[930]) * static_cast<int>(state[2]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[962]) * static_cast<int>(state[2]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[994]) * static_cast<int>(state[2]) * static_cast<int>(state[31]);
    }
    if (state[3]) {
        sum += static_cast<int>(matrix[99]) * static_cast<int>(state[3]) * static_cast<int>(state[3]);
        if (state[4])
            sum += static_cast<int>(matrix[131]) * static_cast<int>(state[3]) * static_cast<int>(state[4]);
        if (state[5])
            sum += static_cast<int>(matrix[163]) * static_cast<int>(state[3]) * static_cast<int>(state[5]);
        if (state[6])
            sum += static_cast<int>(matrix[195]) * static_cast<int>(state[3]) * static_cast<int>(state[6]);
        if (state[7])
            sum += static_cast<int>(matrix[227]) * static_cast<int>(state[3]) * static_cast<int>(state[7]);
        if (state[8])
            sum += static_cast<int>(matrix[259]) * static_cast<int>(state[3]) * static_cast<int>(state[8]);
        if (state[9])
            sum += static_cast<int>(matrix[291]) * static_cast<int>(state[3]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[323]) * static_cast<int>(state[3]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[355]) * static_cast<int>(state[3]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[387]) * static_cast<int>(state[3]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[419]) * static_cast<int>(state[3]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[451]) * static_cast<int>(state[3]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[483]) * static_cast<int>(state[3]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[515]) * static_cast<int>(state[3]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[547]) * static_cast<int>(state[3]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[579]) * static_cast<int>(state[3]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[611]) * static_cast<int>(state[3]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[643]) * static_cast<int>(state[3]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[675]) * static_cast<int>(state[3]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[707]) * static_cast<int>(state[3]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[739]) * static_cast<int>(state[3]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[771]) * static_cast<int>(state[3]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[803]) * static_cast<int>(state[3]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[835]) * static_cast<int>(state[3]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[867]) * static_cast<int>(state[3]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[899]) * static_cast<int>(state[3]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[931]) * static_cast<int>(state[3]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[963]) * static_cast<int>(state[3]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[995]) * static_cast<int>(state[3]) * static_cast<int>(state[31]);
    }
    if (state[4]) {
        sum += static_cast<int>(matrix[132]) * static_cast<int>(state[4]) * static_cast<int>(state[4]);
        if (state[5])
            sum += static_cast<int>(matrix[164]) * static_cast<int>(state[4]) * static_cast<int>(state[5]);
        if (state[6])
            sum += static_cast<int>(matrix[196]) * static_cast<int>(state[4]) * static_cast<int>(state[6]);
        if (state[7])
            sum += static_cast<int>(matrix[228]) * static_cast<int>(state[4]) * static_cast<int>(state[7]);
        if (state[8])
            sum += static_cast<int>(matrix[260]) * static_cast<int>(state[4]) * static_cast<int>(state[8]);
        if (state[9])
            sum += static_cast<int>(matrix[292]) * static_cast<int>(state[4]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[324]) * static_cast<int>(state[4]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[356]) * static_cast<int>(state[4]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[388]) * static_cast<int>(state[4]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[420]) * static_cast<int>(state[4]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[452]) * static_cast<int>(state[4]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[484]) * static_cast<int>(state[4]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[516]) * static_cast<int>(state[4]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[548]) * static_cast<int>(state[4]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[580]) * static_cast<int>(state[4]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[612]) * static_cast<int>(state[4]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[644]) * static_cast<int>(state[4]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[676]) * static_cast<int>(state[4]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[708]) * static_cast<int>(state[4]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[740]) * static_cast<int>(state[4]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[772]) * static_cast<int>(state[4]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[804]) * static_cast<int>(state[4]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[836]) * static_cast<int>(state[4]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[868]) * static_cast<int>(state[4]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[900]) * static_cast<int>(state[4]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[932]) * static_cast<int>(state[4]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[964]) * static_cast<int>(state[4]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[996]) * static_cast<int>(state[4]) * static_cast<int>(state[31]);
    }
    if (state[5]) {
        sum += static_cast<int>(matrix[165]) * static_cast<int>(state[5]) * static_cast<int>(state[5]);
        if (state[6])
            sum += static_cast<int>(matrix[197]) * static_cast<int>(state[5]) * static_cast<int>(state[6]);
        if (state[7])
            sum += static_cast<int>(matrix[229]) * static_cast<int>(state[5]) * static_cast<int>(state[7]);
        if (state[8])
            sum += static_cast<int>(matrix[261]) * static_cast<int>(state[5]) * static_cast<int>(state[8]);
        if (state[9])
            sum += static_cast<int>(matrix[293]) * static_cast<int>(state[5]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[325]) * static_cast<int>(state[5]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[357]) * static_cast<int>(state[5]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[389]) * static_cast<int>(state[5]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[421]) * static_cast<int>(state[5]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[453]) * static_cast<int>(state[5]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[485]) * static_cast<int>(state[5]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[517]) * static_cast<int>(state[5]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[549]) * static_cast<int>(state[5]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[581]) * static_cast<int>(state[5]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[613]) * static_cast<int>(state[5]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[645]) * static_cast<int>(state[5]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[677]) * static_cast<int>(state[5]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[709]) * static_cast<int>(state[5]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[741]) * static_cast<int>(state[5]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[773]) * static_cast<int>(state[5]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[805]) * static_cast<int>(state[5]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[837]) * static_cast<int>(state[5]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[869]) * static_cast<int>(state[5]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[901]) * static_cast<int>(state[5]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[933]) * static_cast<int>(state[5]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[965]) * static_cast<int>(state[5]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[997]) * static_cast<int>(state[5]) * static_cast<int>(state[31]);
    }
    if (state[6]) {
        sum += static_cast<int>(matrix[198]) * static_cast<int>(state[6]) * static_cast<int>(state[6]);
        if (state[7])
            sum += static_cast<int>(matrix[230]) * static_cast<int>(state[6]) * static_cast<int>(state[7]);
        if (state[8])
            sum += static_cast<int>(matrix[262]) * static_cast<int>(state[6]) * static_cast<int>(state[8]);
        if (state[9])
            sum += static_cast<int>(matrix[294]) * static_cast<int>(state[6]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[326]) * static_cast<int>(state[6]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[358]) * static_cast<int>(state[6]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[390]) * static_cast<int>(state[6]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[422]) * static_cast<int>(state[6]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[454]) * static_cast<int>(state[6]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[486]) * static_cast<int>(state[6]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[518]) * static_cast<int>(state[6]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[550]) * static_cast<int>(state[6]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[582]) * static_cast<int>(state[6]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[614]) * static_cast<int>(state[6]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[646]) * static_cast<int>(state[6]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[678]) * static_cast<int>(state[6]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[710]) * static_cast<int>(state[6]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[742]) * static_cast<int>(state[6]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[774]) * static_cast<int>(state[6]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[806]) * static_cast<int>(state[6]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[838]) * static_cast<int>(state[6]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[870]) * static_cast<int>(state[6]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[902]) * static_cast<int>(state[6]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[934]) * static_cast<int>(state[6]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[966]) * static_cast<int>(state[6]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[998]) * static_cast<int>(state[6]) * static_cast<int>(state[31]);
    }
    if (state[7]) {
        sum += static_cast<int>(matrix[231]) * static_cast<int>(state[7]) * static_cast<int>(state[7]);
        if (state[8])
            sum += static_cast<int>(matrix[263]) * static_cast<int>(state[7]) * static_cast<int>(state[8]);
        if (state[9])
            sum += static_cast<int>(matrix[295]) * static_cast<int>(state[7]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[327]) * static_cast<int>(state[7]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[359]) * static_cast<int>(state[7]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[391]) * static_cast<int>(state[7]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[423]) * static_cast<int>(state[7]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[455]) * static_cast<int>(state[7]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[487]) * static_cast<int>(state[7]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[519]) * static_cast<int>(state[7]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[551]) * static_cast<int>(state[7]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[583]) * static_cast<int>(state[7]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[615]) * static_cast<int>(state[7]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[647]) * static_cast<int>(state[7]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[679]) * static_cast<int>(state[7]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[711]) * static_cast<int>(state[7]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[743]) * static_cast<int>(state[7]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[775]) * static_cast<int>(state[7]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[807]) * static_cast<int>(state[7]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[839]) * static_cast<int>(state[7]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[871]) * static_cast<int>(state[7]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[903]) * static_cast<int>(state[7]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[935]) * static_cast<int>(state[7]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[967]) * static_cast<int>(state[7]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[999]) * static_cast<int>(state[7]) * static_cast<int>(state[31]);
    }
    if (state[8]) {
        sum += static_cast<int>(matrix[264]) * static_cast<int>(state[8]) * static_cast<int>(state[8]);
        if (state[9])
            sum += static_cast<int>(matrix[296]) * static_cast<int>(state[8]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[328]) * static_cast<int>(state[8]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[360]) * static_cast<int>(state[8]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[392]) * static_cast<int>(state[8]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[424]) * static_cast<int>(state[8]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[456]) * static_cast<int>(state[8]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[488]) * static_cast<int>(state[8]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[520]) * static_cast<int>(state[8]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[552]) * static_cast<int>(state[8]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[584]) * static_cast<int>(state[8]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[616]) * static_cast<int>(state[8]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[648]) * static_cast<int>(state[8]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[680]) * static_cast<int>(state[8]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[712]) * static_cast<int>(state[8]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[744]) * static_cast<int>(state[8]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[776]) * static_cast<int>(state[8]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[808]) * static_cast<int>(state[8]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[840]) * static_cast<int>(state[8]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[872]) * static_cast<int>(state[8]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[904]) * static_cast<int>(state[8]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[936]) * static_cast<int>(state[8]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[968]) * static_cast<int>(state[8]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1000]) * static_cast<int>(state[8]) * static_cast<int>(state[31]);
    }
    if (state[9]) {
        sum += static_cast<int>(matrix[297]) * static_cast<int>(state[9]) * static_cast<int>(state[9]);
        if (state[10])
            sum += static_cast<int>(matrix[329]) * static_cast<int>(state[9]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[361]) * static_cast<int>(state[9]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[393]) * static_cast<int>(state[9]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[425]) * static_cast<int>(state[9]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[457]) * static_cast<int>(state[9]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[489]) * static_cast<int>(state[9]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[521]) * static_cast<int>(state[9]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[553]) * static_cast<int>(state[9]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[585]) * static_cast<int>(state[9]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[617]) * static_cast<int>(state[9]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[649]) * static_cast<int>(state[9]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[681]) * static_cast<int>(state[9]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[713]) * static_cast<int>(state[9]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[745]) * static_cast<int>(state[9]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[777]) * static_cast<int>(state[9]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[809]) * static_cast<int>(state[9]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[841]) * static_cast<int>(state[9]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[873]) * static_cast<int>(state[9]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[905]) * static_cast<int>(state[9]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[937]) * static_cast<int>(state[9]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[969]) * static_cast<int>(state[9]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1001]) * static_cast<int>(state[9]) * static_cast<int>(state[31]);
    }
    if (state[10]) {
        sum += static_cast<int>(matrix[330]) * static_cast<int>(state[10]) * static_cast<int>(state[10]);
        if (state[11])
            sum += static_cast<int>(matrix[362]) * static_cast<int>(state[10]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[394]) * static_cast<int>(state[10]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[426]) * static_cast<int>(state[10]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[458]) * static_cast<int>(state[10]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[490]) * static_cast<int>(state[10]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[522]) * static_cast<int>(state[10]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[554]) * static_cast<int>(state[10]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[586]) * static_cast<int>(state[10]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[618]) * static_cast<int>(state[10]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[650]) * static_cast<int>(state[10]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[682]) * static_cast<int>(state[10]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[714]) * static_cast<int>(state[10]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[746]) * static_cast<int>(state[10]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[778]) * static_cast<int>(state[10]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[810]) * static_cast<int>(state[10]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[842]) * static_cast<int>(state[10]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[874]) * static_cast<int>(state[10]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[906]) * static_cast<int>(state[10]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[938]) * static_cast<int>(state[10]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[970]) * static_cast<int>(state[10]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1002]) * static_cast<int>(state[10]) * static_cast<int>(state[31]);
    }
    if (state[11]) {
        sum += static_cast<int>(matrix[363]) * static_cast<int>(state[11]) * static_cast<int>(state[11]);
        if (state[12])
            sum += static_cast<int>(matrix[395]) * static_cast<int>(state[11]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[427]) * static_cast<int>(state[11]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[459]) * static_cast<int>(state[11]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[491]) * static_cast<int>(state[11]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[523]) * static_cast<int>(state[11]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[555]) * static_cast<int>(state[11]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[587]) * static_cast<int>(state[11]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[619]) * static_cast<int>(state[11]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[651]) * static_cast<int>(state[11]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[683]) * static_cast<int>(state[11]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[715]) * static_cast<int>(state[11]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[747]) * static_cast<int>(state[11]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[779]) * static_cast<int>(state[11]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[811]) * static_cast<int>(state[11]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[843]) * static_cast<int>(state[11]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[875]) * static_cast<int>(state[11]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[907]) * static_cast<int>(state[11]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[939]) * static_cast<int>(state[11]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[971]) * static_cast<int>(state[11]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1003]) * static_cast<int>(state[11]) * static_cast<int>(state[31]);
    }
    if (state[12]) {
        sum += static_cast<int>(matrix[396]) * static_cast<int>(state[12]) * static_cast<int>(state[12]);
        if (state[13])
            sum += static_cast<int>(matrix[428]) * static_cast<int>(state[12]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[460]) * static_cast<int>(state[12]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[492]) * static_cast<int>(state[12]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[524]) * static_cast<int>(state[12]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[556]) * static_cast<int>(state[12]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[588]) * static_cast<int>(state[12]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[620]) * static_cast<int>(state[12]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[652]) * static_cast<int>(state[12]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[684]) * static_cast<int>(state[12]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[716]) * static_cast<int>(state[12]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[748]) * static_cast<int>(state[12]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[780]) * static_cast<int>(state[12]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[812]) * static_cast<int>(state[12]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[844]) * static_cast<int>(state[12]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[876]) * static_cast<int>(state[12]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[908]) * static_cast<int>(state[12]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[940]) * static_cast<int>(state[12]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[972]) * static_cast<int>(state[12]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1004]) * static_cast<int>(state[12]) * static_cast<int>(state[31]);
    }
    if (state[13]) {
        sum += static_cast<int>(matrix[429]) * static_cast<int>(state[13]) * static_cast<int>(state[13]);
        if (state[14])
            sum += static_cast<int>(matrix[461]) * static_cast<int>(state[13]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[493]) * static_cast<int>(state[13]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[525]) * static_cast<int>(state[13]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[557]) * static_cast<int>(state[13]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[589]) * static_cast<int>(state[13]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[621]) * static_cast<int>(state[13]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[653]) * static_cast<int>(state[13]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[685]) * static_cast<int>(state[13]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[717]) * static_cast<int>(state[13]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[749]) * static_cast<int>(state[13]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[781]) * static_cast<int>(state[13]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[813]) * static_cast<int>(state[13]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[845]) * static_cast<int>(state[13]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[877]) * static_cast<int>(state[13]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[909]) * static_cast<int>(state[13]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[941]) * static_cast<int>(state[13]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[973]) * static_cast<int>(state[13]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1005]) * static_cast<int>(state[13]) * static_cast<int>(state[31]);
    }
    if (state[14]) {
        sum += static_cast<int>(matrix[462]) * static_cast<int>(state[14]) * static_cast<int>(state[14]);
        if (state[15])
            sum += static_cast<int>(matrix[494]) * static_cast<int>(state[14]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[526]) * static_cast<int>(state[14]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[558]) * static_cast<int>(state[14]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[590]) * static_cast<int>(state[14]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[622]) * static_cast<int>(state[14]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[654]) * static_cast<int>(state[14]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[686]) * static_cast<int>(state[14]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[718]) * static_cast<int>(state[14]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[750]) * static_cast<int>(state[14]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[782]) * static_cast<int>(state[14]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[814]) * static_cast<int>(state[14]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[846]) * static_cast<int>(state[14]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[878]) * static_cast<int>(state[14]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[910]) * static_cast<int>(state[14]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[942]) * static_cast<int>(state[14]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[974]) * static_cast<int>(state[14]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1006]) * static_cast<int>(state[14]) * static_cast<int>(state[31]);
    } if (state[15]) {
        sum += static_cast<int>(matrix[495]) * static_cast<int>(state[15]) * static_cast<int>(state[15]);
        if (state[16])
            sum += static_cast<int>(matrix[527]) * static_cast<int>(state[15]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[559]) * static_cast<int>(state[15]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[591]) * static_cast<int>(state[15]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[623]) * static_cast<int>(state[15]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[655]) * static_cast<int>(state[15]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[687]) * static_cast<int>(state[15]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[719]) * static_cast<int>(state[15]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[751]) * static_cast<int>(state[15]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[783]) * static_cast<int>(state[15]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[815]) * static_cast<int>(state[15]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[847]) * static_cast<int>(state[15]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[879]) * static_cast<int>(state[15]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[911]) * static_cast<int>(state[15]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[943]) * static_cast<int>(state[15]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[975]) * static_cast<int>(state[15]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1007]) * static_cast<int>(state[15]) * static_cast<int>(state[31]);
    }
    if (state[16]) {
        sum += static_cast<int>(matrix[528]) * static_cast<int>(state[16]) * static_cast<int>(state[16]);
        if (state[17])
            sum += static_cast<int>(matrix[560]) * static_cast<int>(state[16]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[592]) * static_cast<int>(state[16]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[624]) * static_cast<int>(state[16]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[656]) * static_cast<int>(state[16]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[688]) * static_cast<int>(state[16]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[720]) * static_cast<int>(state[16]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[752]) * static_cast<int>(state[16]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[784]) * static_cast<int>(state[16]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[816]) * static_cast<int>(state[16]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[848]) * static_cast<int>(state[16]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[880]) * static_cast<int>(state[16]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[912]) * static_cast<int>(state[16]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[944]) * static_cast<int>(state[16]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[976]) * static_cast<int>(state[16]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1008]) * static_cast<int>(state[16]) * static_cast<int>(state[31]);
    }
    if (state[17]) {
        sum += static_cast<int>(matrix[561]) * static_cast<int>(state[17]) * static_cast<int>(state[17]);
        if (state[18])
            sum += static_cast<int>(matrix[593]) * static_cast<int>(state[17]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[625]) * static_cast<int>(state[17]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[657]) * static_cast<int>(state[17]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[689]) * static_cast<int>(state[17]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[721]) * static_cast<int>(state[17]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[753]) * static_cast<int>(state[17]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[785]) * static_cast<int>(state[17]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[817]) * static_cast<int>(state[17]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[849]) * static_cast<int>(state[17]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[881]) * static_cast<int>(state[17]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[913]) * static_cast<int>(state[17]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[945]) * static_cast<int>(state[17]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[977]) * static_cast<int>(state[17]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1009]) * static_cast<int>(state[17]) * static_cast<int>(state[31]);
    }
    if (state[18]) {
        sum += static_cast<int>(matrix[594]) * static_cast<int>(state[18]) * static_cast<int>(state[18]);
        if (state[19])
            sum += static_cast<int>(matrix[626]) * static_cast<int>(state[18]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[658]) * static_cast<int>(state[18]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[690]) * static_cast<int>(state[18]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[722]) * static_cast<int>(state[18]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[754]) * static_cast<int>(state[18]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[786]) * static_cast<int>(state[18]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[818]) * static_cast<int>(state[18]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[850]) * static_cast<int>(state[18]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[882]) * static_cast<int>(state[18]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[914]) * static_cast<int>(state[18]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[946]) * static_cast<int>(state[18]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[978]) * static_cast<int>(state[18]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1010]) * static_cast<int>(state[18]) * static_cast<int>(state[31]);
    }
    if (state[19]) {
        sum += static_cast<int>(matrix[627]) * static_cast<int>(state[19]) * static_cast<int>(state[19]);
        if (state[20])
            sum += static_cast<int>(matrix[659]) * static_cast<int>(state[19]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[691]) * static_cast<int>(state[19]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[723]) * static_cast<int>(state[19]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[755]) * static_cast<int>(state[19]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[787]) * static_cast<int>(state[19]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[819]) * static_cast<int>(state[19]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[851]) * static_cast<int>(state[19]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[883]) * static_cast<int>(state[19]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[915]) * static_cast<int>(state[19]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[947]) * static_cast<int>(state[19]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[979]) * static_cast<int>(state[19]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1011]) * static_cast<int>(state[19]) * static_cast<int>(state[31]);
    }
    if (state[20]) {
        sum += static_cast<int>(matrix[660]) * static_cast<int>(state[20]) * static_cast<int>(state[20]);
        if (state[21])
            sum += static_cast<int>(matrix[692]) * static_cast<int>(state[20]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[724]) * static_cast<int>(state[20]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[756]) * static_cast<int>(state[20]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[788]) * static_cast<int>(state[20]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[820]) * static_cast<int>(state[20]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[852]) * static_cast<int>(state[20]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[884]) * static_cast<int>(state[20]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[916]) * static_cast<int>(state[20]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[948]) * static_cast<int>(state[20]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[980]) * static_cast<int>(state[20]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1012]) * static_cast<int>(state[20]) * static_cast<int>(state[31]);
    }
    if (state[21]) {
        sum += static_cast<int>(matrix[693]) * static_cast<int>(state[21]) * static_cast<int>(state[21]);
        if (state[22])
            sum += static_cast<int>(matrix[725]) * static_cast<int>(state[21]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[757]) * static_cast<int>(state[21]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[789]) * static_cast<int>(state[21]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[821]) * static_cast<int>(state[21]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[853]) * static_cast<int>(state[21]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[885]) * static_cast<int>(state[21]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[917]) * static_cast<int>(state[21]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[949]) * static_cast<int>(state[21]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[981]) * static_cast<int>(state[21]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1013]) * static_cast<int>(state[21]) * static_cast<int>(state[31]);
    }
    if (state[22]) {
        sum += static_cast<int>(matrix[726]) * static_cast<int>(state[22]) * static_cast<int>(state[22]);
        if (state[23])
            sum += static_cast<int>(matrix[758]) * static_cast<int>(state[22]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[790]) * static_cast<int>(state[22]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[822]) * static_cast<int>(state[22]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[854]) * static_cast<int>(state[22]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[886]) * static_cast<int>(state[22]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[918]) * static_cast<int>(state[22]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[950]) * static_cast<int>(state[22]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[982]) * static_cast<int>(state[22]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1014]) * static_cast<int>(state[22]) * static_cast<int>(state[31]);
    }
    {
        if (state[23])
            sum += static_cast<int>(matrix[759]) * static_cast<int>(state[23]) * static_cast<int>(state[23]);
        if (state[24])
            sum += static_cast<int>(matrix[791]) * static_cast<int>(state[23]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[823]) * static_cast<int>(state[23]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[855]) * static_cast<int>(state[23]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[887]) * static_cast<int>(state[23]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[919]) * static_cast<int>(state[23]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[951]) * static_cast<int>(state[23]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[983]) * static_cast<int>(state[23]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1015]) * static_cast<int>(state[23]) * static_cast<int>(state[31]);
    }
    if (state[24]) {
        sum += static_cast<int>(matrix[792]) * static_cast<int>(state[24]) * static_cast<int>(state[24]);
        if (state[25])
            sum += static_cast<int>(matrix[824]) * static_cast<int>(state[24]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[856]) * static_cast<int>(state[24]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[888]) * static_cast<int>(state[24]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[920]) * static_cast<int>(state[24]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[952]) * static_cast<int>(state[24]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[984]) * static_cast<int>(state[24]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1016]) * static_cast<int>(state[24]) * static_cast<int>(state[31]);
    }
    if (state[25]) {
        sum += static_cast<int>(matrix[825]) * static_cast<int>(state[25]) * static_cast<int>(state[25]);
        if (state[26])
            sum += static_cast<int>(matrix[857]) * static_cast<int>(state[25]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[889]) * static_cast<int>(state[25]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[921]) * static_cast<int>(state[25]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[953]) * static_cast<int>(state[25]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[985]) * static_cast<int>(state[25]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1017]) * static_cast<int>(state[25]) * static_cast<int>(state[31]);
    }
    if (state[26]) {
        sum += static_cast<int>(matrix[858]) * static_cast<int>(state[26]) * static_cast<int>(state[26]);
        if (state[27])
            sum += static_cast<int>(matrix[890]) * static_cast<int>(state[26]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[922]) * static_cast<int>(state[26]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[954]) * static_cast<int>(state[26]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[986]) * static_cast<int>(state[26]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1018]) * static_cast<int>(state[26]) * static_cast<int>(state[31]);
    }
    if (state[27]) {
        sum += static_cast<int>(matrix[891]) * static_cast<int>(state[27]) * static_cast<int>(state[27]);
        if (state[28])
            sum += static_cast<int>(matrix[923]) * static_cast<int>(state[27]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[955]) * static_cast<int>(state[27]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[987]) * static_cast<int>(state[27]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1019]) * static_cast<int>(state[27]) * static_cast<int>(state[31]);
    }
    if (state[28]) {
        sum += static_cast<int>(matrix[924]) * static_cast<int>(state[28]) * static_cast<int>(state[28]);
        if (state[29])
            sum += static_cast<int>(matrix[956]) * static_cast<int>(state[28]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[988]) * static_cast<int>(state[28]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1020]) * static_cast<int>(state[28]) * static_cast<int>(state[31]);
    }
    if (state[29])
    {
        sum += static_cast<int>(matrix[957]) * static_cast<int>(state[29]) * static_cast<int>(state[29]);
        if (state[30])
            sum += static_cast<int>(matrix[989]) * static_cast<int>(state[29]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1021]) * static_cast<int>(state[29]) * static_cast<int>(state[31]);
    }
    if (state[30])
    {
        sum += static_cast<int>(matrix[990]) * static_cast<int>(state[30]) * static_cast<int>(state[30]);
        if (state[31])
            sum += static_cast<int>(matrix[1022]) * static_cast<int>(state[30]) * static_cast<int>(state[31]);
    }
    if (state[31])
        sum += static_cast<int>(matrix[1023]) * static_cast<int>(state[31]) * static_cast<int>(state[31]);

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
    return "8-bit state vector, with full 8bit dense value matrix without AVX, manually unrolled";
}

bool ignoreOutput() {return false;}