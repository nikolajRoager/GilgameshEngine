//
// Created by nikolaj on 18/02/25.
//

#include <cstdint>
#include <array>
#include <format>
#include <sstream>
#include <string>

#include "valueMatrix_dense_full.h"

#ifndef GILGAMESHENGINE_MAT8BIT_H
#define GILGAMESHENGINE_MAT8BIT_H

#endif //GILGAMESHENGINE_MAT8BIT_H

///@brief 8 bit dense square matrix of AI values, with the 1/4 all 0 block left out, in "counters-in-the-back" format, please open the valueMatrix_dense_3of4_backformat.h file to see a diagram
///@brief Value matrices are from the perspective of player 0, and assumes that it is player 1s turn!
template<typename T, typename =std::enable_if<std::is_integral_v<T>>>
class valueMatrix_dense_3of4_backformat
{

    ///@brief 8 bit dense square matrix of AI values, although the matrix is lower-triangular this version includes all data (simplifying lookup), backformat means that the values associated with unstarted and finished counts are in the back, please open the valueMatrix_dense_3of4_backformat.h file to see a diagram
    std::array<T,32*32-16*16/*We do not store this data, as it is all 0*/> myData=
            //The default data below only illustrate the data structure, the matrix can NOT be default initialized
            //0's below indicate data which must be 0, 1's below indicate data which can be any 8 bit integer
            //This illustration works best, if line-wrap is turned off in your editor
            {

//The first 14 columns are selected if player 0 has a piece in position #
//    # 1 2 3 4 5 6 7 8 9 A B C D E
//      | | | | | | | | | | | | | | The next are selected if player 1 is at position #
//      | | | | | | | | | | | | | |  1 2     3 4 5 6 7 8 9 A B C D E
//      | | | | | | | | | | | | | |  | |     | | | | | | | | | | | | The final 4 get multiplied by:
//      | | | | | | | | | | | | | |  | |     | | | | | | | | | | | |  0 unstarted
//      | | | | | | | | | | | | | |  | |     | | | | | | | | | | | |  | 0 finished
//      | | | | | | | | | | | | | |  | |     | | | | | | | | | | | |  | | 1 unstarted
//      | | | | | | | | | | | | | |  | |     | | | | | | | | | | | |  | | | 1 finished
//      Block A | | | | | | | | | | Block B  | Block C | | | | | | |  Block D
//      | | | | | | | | | | | | | |  | |     | | | | | | | | | | | |  | | | |
//      v v v v v v v v v v v v v v  v v     v v v v v v v v v v v v  v v v v    //Similarly the top 14 columns get selected, if player 0 has a piece at #
        1,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-1
        1,1,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-2
        1,1,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-3
        1,1,1,1,0,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-4
        1,1,1,1,1,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-5
        1,1,1,1,1,1,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-6
        1,1,1,1,1,1,1,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-7
        1,1,1,1,1,1,1,1,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-8
        1,1,1,1,1,1,1,1,1,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-9
        1,1,1,1,1,1,1,1,1,1,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-A
        1,1,1,1,1,1,1,1,1,1,1,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-B
        1,1,1,1,1,1,1,1,1,1,1,1,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-C
        1,1,1,1,1,1,1,1,1,1,1,1,1,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-D
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-E
        //Block E                    Block F  Block G               Block H //And these get selected if player 1 is at #
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-1
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-2
        //Block I                    Block J  Block K               Block L
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-3
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-4
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,0,0,0,0,0,0,0,0,0, 0,0,0,0,//<-5
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,0,0,0,0,0,0,0,0, 0,0,0,0,//<-6
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,0,0,0,0,0,0,0, 0,0,0,0,//<-7
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,0,0,0,0,0,0, 0,0,0,0,//<-8
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,0,0,0,0,0, 0,0,0,0,//<-9
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,0,0,0,0, 0,0,0,0,//<-A
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,0,0,0, 0,0,0,0,//<-B
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,0,0, 0,0,0,0,//<-C
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,0, 0,0,0,0,//<-D
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,//<-E
        //Block M                    Block O  Block P               Block Q     And the final 4 get multiplied by:
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 1,0,0,0,//<-0 unstarted
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 1,1,0,0,//<-0 finished
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,0,//<-1 unstarted
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,//<-1 finished
        //The most logical way to divide up the matrix, would be block A (player 0 0), Blocks B+C+E+F (plyer 0 1, which IS all 0 and can be skipped), Block I+J (Player 1 0) and Block K+L (player 1 1) and finally block M (player 0 and unstarted/finished of both) block O+P (player 1 and unstarted/finished) and finally Block Q (unstarted/finished and unstarted/finished); (Blocks D, H, and L are all 0 and need not be considered)
        //However we need 256 bit per register, so with this matrix, it is more logical to look at the matrix using the blocks: A+B+E+F, skip C+D+G+H, look at I+J, K+L, M+O, and then P+Q,
            };

public:
    ////@brief address of the start of the data
    [[nodiscard]] inline const void* data() const {
        return &(myData[0]);
    }
    ///@brief size of data in bytes
    [[nodiscard]] inline auto byteSize()const{return myData.size()*sizeof (T);}
    ///@brief Template constructor from another matrix with same signedness, but default format
    ///@warning very poor performance, I could not find a good way of mapping the data around
    template<typename U,
            typename =std::enable_if<
                    std::is_integral_v<U>/*redundant, but I like to write it explicitly*/
                    && std::is_signed_v<U> == std::is_signed_v<T>//Same signedness required
            >
            > explicit valueMatrix_dense_3of4_backformat(const valueMatrix_dense_full<U>& data)
    {
        /*This outcommented version shows how ALL the data really should be mapped
         *Please do not delete, I find it useful to explain how the data layout work
        myData={
            data[1+32*1] ,data[2+32*1] ,data[3+32*1] ,data[4+32*1] ,data[5+32*1] ,data[6+32*1] ,data[7+32*1] ,data[8+32*1] ,data[9+32*1] ,data[10+32*1] ,data[11+32*1] ,data[12+32*1] ,data[13+32*1] ,data[14+32*1] ,data[17+32*1] ,data[18+32*1],
            data[1+32*2] ,data[2+32*2] ,data[3+32*2] ,data[4+32*2] ,data[5+32*2] ,data[6+32*2] ,data[7+32*2] ,data[8+32*2] ,data[9+32*2] ,data[10+32*2] ,data[11+32*2] ,data[12+32*2] ,data[13+32*2] ,data[14+32*2] ,data[17+32*2] ,data[18+32*2],
            data[1+32*3] ,data[2+32*3] ,data[3+32*3] ,data[4+32*3] ,data[5+32*3] ,data[6+32*3] ,data[7+32*3] ,data[8+32*3] ,data[9+32*3] ,data[10+32*3] ,data[11+32*3] ,data[12+32*3] ,data[13+32*3] ,data[14+32*3] ,data[17+32*3] ,data[18+32*3],
            data[1+32*4] ,data[2+32*4] ,data[3+32*4] ,data[4+32*4] ,data[5+32*4] ,data[6+32*4] ,data[7+32*4] ,data[8+32*4] ,data[9+32*4] ,data[10+32*4] ,data[11+32*4] ,data[12+32*4] ,data[13+32*4] ,data[14+32*4] ,data[17+32*4] ,data[18+32*4],
            data[1+32*5] ,data[2+32*5] ,data[3+32*5] ,data[4+32*5] ,data[5+32*5] ,data[6+32*5] ,data[7+32*5] ,data[8+32*5] ,data[9+32*5] ,data[10+32*5] ,data[11+32*5] ,data[12+32*5] ,data[13+32*5] ,data[14+32*5] ,data[17+32*5] ,data[18+32*5],
            data[1+32*6] ,data[2+32*6] ,data[3+32*6] ,data[4+32*6] ,data[5+32*6] ,data[6+32*6] ,data[7+32*6] ,data[8+32*6] ,data[9+32*6] ,data[10+32*6] ,data[11+32*6] ,data[12+32*6] ,data[13+32*6] ,data[14+32*6] ,data[17+32*6] ,data[18+32*6],
            data[1+32*7] ,data[2+32*7] ,data[3+32*7] ,data[4+32*7] ,data[5+32*7] ,data[6+32*7] ,data[7+32*7] ,data[8+32*7] ,data[9+32*7] ,data[10+32*7] ,data[11+32*7] ,data[12+32*7] ,data[13+32*7] ,data[14+32*7] ,data[17+32*7] ,data[18+32*7],
            data[1+32*8] ,data[2+32*8] ,data[3+32*8] ,data[4+32*8] ,data[5+32*8] ,data[6+32*8] ,data[7+32*8] ,data[8+32*8] ,data[9+32*8] ,data[10+32*8] ,data[11+32*8] ,data[12+32*8] ,data[13+32*8] ,data[14+32*8] ,data[17+32*8] ,data[18+32*8],
            data[1+32*9] ,data[2+32*9] ,data[3+32*9] ,data[4+32*9] ,data[5+32*9] ,data[6+32*9] ,data[7+32*9] ,data[8+32*9] ,data[9+32*9] ,data[10+32*9] ,data[11+32*9] ,data[12+32*9] ,data[13+32*9] ,data[14+32*9] ,data[17+32*9] ,data[18+32*9],
            data[1+32*10],data[2+32*10],data[3+32*10],data[4+32*10],data[5+32*10],data[6+32*10],data[7+32*10],data[8+32*10],data[9+32*10],data[10+32*10],data[11+32*10],data[12+32*10],data[13+32*10],data[14+32*10],data[17+32*10],data[18+32*10],
            data[1+32*11],data[2+32*11],data[3+32*11],data[4+32*11],data[5+32*11],data[6+32*11],data[7+32*11],data[8+32*11],data[9+32*11],data[10+32*11],data[11+32*11],data[12+32*11],data[13+32*11],data[14+32*11],data[17+32*11],data[18+32*11],
            data[1+32*12],data[2+32*12],data[3+32*12],data[4+32*12],data[5+32*12],data[6+32*12],data[7+32*12],data[8+32*12],data[9+32*12],data[10+32*12],data[11+32*12],data[12+32*12],data[13+32*12],data[14+32*12],data[17+32*12],data[18+32*12],
            data[1+32*13],data[2+32*13],data[3+32*13],data[4+32*13],data[5+32*13],data[6+32*13],data[7+32*13],data[8+32*13],data[9+32*13],data[10+32*13],data[11+32*13],data[12+32*13],data[13+32*13],data[14+32*13],data[17+32*13],data[18+32*13],
            data[1+32*14],data[2+32*14],data[3+32*14],data[4+32*14],data[5+32*14],data[6+32*14],data[7+32*14],data[8+32*14],data[9+32*14],data[10+32*14],data[11+32*14],data[12+32*14],data[13+32*14],data[14+32*14],data[17+32*14],data[18+32*14],
                                                                                                                                                                                                                                                                                                                                                                                                                                            //rows[0][17:30] rows[15][17:30] rows[16][17:30] normal column 31
             data[1+32*17],data[2+32*17],data[3+32*17],data[4+32*17],data[5+32*17],data[6+32*17],data[7+32*17],data[8+32*17],data[9+32*17],data[10+32*17],data[11+32*17],data[12+32*17],data[13+32*17],data[14+32*17],data[17+32*17],data[18+32*17],  data[19+32*17],data[20+32*17],data[21+32*17],data[22+32*17],data[23+32*17],data[24+32*17],data[25+32*17],data[26+32*17],data[27+32*17],data[28+32*17],data[29+32*17],data[30+32*17],  data[17+32*0],data[17+32*15],data[17+32*16],data[31+32*17],
             data[1+32*18],data[2+32*18],data[3+32*18],data[4+32*18],data[5+32*18],data[6+32*18],data[7+32*18],data[8+32*18],data[9+32*18],data[10+32*18],data[11+32*18],data[12+32*18],data[13+32*18],data[14+32*18],data[17+32*18],data[18+32*18],  data[19+32*18],data[20+32*18],data[21+32*18],data[22+32*18],data[23+32*18],data[24+32*18],data[25+32*18],data[26+32*18],data[27+32*18],data[28+32*18],data[29+32*18],data[30+32*18],  data[18+32*0],data[18+32*15],data[18+32*16],data[31+32*18],
             data[1+32*19],data[2+32*19],data[3+32*19],data[4+32*19],data[5+32*19],data[6+32*19],data[7+32*19],data[8+32*19],data[9+32*19],data[10+32*19],data[11+32*19],data[12+32*19],data[13+32*19],data[14+32*19],data[17+32*19],data[18+32*19],  data[19+32*19],data[20+32*19],data[21+32*19],data[22+32*19],data[23+32*19],data[24+32*19],data[25+32*19],data[26+32*19],data[27+32*19],data[28+32*19],data[29+32*19],data[30+32*19],  data[19+32*0],data[19+32*15],data[19+32*16],data[31+32*19],
             data[1+32*20],data[2+32*20],data[3+32*20],data[4+32*20],data[5+32*20],data[6+32*20],data[7+32*20],data[8+32*20],data[9+32*20],data[10+32*20],data[11+32*20],data[12+32*20],data[13+32*20],data[14+32*20],data[17+32*20],data[18+32*20],  data[19+32*20],data[20+32*20],data[21+32*20],data[22+32*20],data[23+32*20],data[24+32*20],data[25+32*20],data[26+32*20],data[27+32*20],data[28+32*20],data[29+32*20],data[30+32*20],  data[20+32*0],data[20+32*15],data[20+32*16],data[31+32*20],
             data[1+32*21],data[2+32*21],data[3+32*21],data[4+32*21],data[5+32*21],data[6+32*21],data[7+32*21],data[8+32*21],data[9+32*21],data[10+32*21],data[11+32*21],data[12+32*21],data[13+32*21],data[14+32*21],data[17+32*21],data[18+32*21],  data[19+32*21],data[20+32*21],data[21+32*21],data[22+32*21],data[23+32*21],data[24+32*21],data[25+32*21],data[26+32*21],data[27+32*21],data[28+32*21],data[29+32*21],data[30+32*21],  data[21+32*0],data[21+32*15],data[21+32*16],data[31+32*21],
             data[1+32*22],data[2+32*22],data[3+32*22],data[4+32*22],data[5+32*22],data[6+32*22],data[7+32*22],data[8+32*22],data[9+32*22],data[10+32*22],data[11+32*22],data[12+32*22],data[13+32*22],data[14+32*22],data[17+32*22],data[18+32*22],  data[19+32*22],data[20+32*22],data[21+32*22],data[22+32*22],data[23+32*22],data[24+32*22],data[25+32*22],data[26+32*22],data[27+32*22],data[28+32*22],data[29+32*22],data[30+32*22],  data[22+32*0],data[22+32*15],data[22+32*16],data[31+32*22],
             data[1+32*23],data[2+32*23],data[3+32*23],data[4+32*23],data[5+32*23],data[6+32*23],data[7+32*23],data[8+32*23],data[9+32*23],data[10+32*23],data[11+32*23],data[12+32*23],data[13+32*23],data[14+32*23],data[17+32*23],data[18+32*23],  data[19+32*23],data[20+32*23],data[21+32*23],data[22+32*23],data[23+32*23],data[24+32*23],data[25+32*23],data[26+32*23],data[27+32*23],data[28+32*23],data[29+32*23],data[30+32*23],  data[23+32*0],data[23+32*15],data[23+32*16],data[31+32*23],
             data[1+32*24],data[2+32*24],data[3+32*24],data[4+32*24],data[5+32*24],data[6+32*24],data[7+32*24],data[8+32*24],data[9+32*24],data[10+32*24],data[11+32*24],data[12+32*24],data[13+32*24],data[14+32*24],data[17+32*24],data[18+32*24],  data[19+32*24],data[20+32*24],data[21+32*24],data[22+32*24],data[23+32*24],data[24+32*24],data[25+32*24],data[26+32*24],data[27+32*24],data[28+32*24],data[29+32*24],data[30+32*24],  data[24+32*0],data[24+32*15],data[24+32*16],data[31+32*24],
             data[1+32*25],data[2+32*25],data[3+32*25],data[4+32*25],data[5+32*25],data[6+32*25],data[7+32*25],data[8+32*25],data[9+32*25],data[10+32*25],data[11+32*25],data[12+32*25],data[13+32*25],data[14+32*25],data[17+32*25],data[18+32*25],  data[19+32*25],data[20+32*25],data[21+32*25],data[22+32*25],data[23+32*25],data[24+32*25],data[25+32*25],data[26+32*25],data[27+32*25],data[28+32*25],data[29+32*25],data[30+32*25],  data[25+32*0],data[25+32*15],data[25+32*16],data[31+32*25],
             data[1+32*26],data[2+32*26],data[3+32*26],data[4+32*26],data[5+32*26],data[6+32*26],data[7+32*26],data[8+32*26],data[9+32*26],data[10+32*26],data[11+32*26],data[12+32*26],data[13+32*26],data[14+32*26],data[17+32*26],data[18+32*26],  data[19+32*26],data[20+32*26],data[21+32*26],data[22+32*26],data[23+32*26],data[24+32*26],data[25+32*26],data[26+32*26],data[27+32*26],data[28+32*26],data[29+32*26],data[30+32*26],  data[26+32*0],data[26+32*15],data[26+32*16],data[31+32*26],
             data[1+32*27],data[2+32*27],data[3+32*27],data[4+32*27],data[5+32*27],data[6+32*27],data[7+32*27],data[8+32*27],data[9+32*27],data[10+32*27],data[11+32*27],data[12+32*27],data[13+32*27],data[14+32*27],data[17+32*27],data[18+32*27],  data[19+32*27],data[20+32*27],data[21+32*27],data[22+32*27],data[23+32*27],data[24+32*27],data[25+32*27],data[26+32*27],data[27+32*27],data[28+32*27],data[29+32*27],data[30+32*27],  data[27+32*0],data[27+32*15],data[27+32*16],data[31+32*27],
             data[1+32*28],data[2+32*28],data[3+32*28],data[4+32*28],data[5+32*28],data[6+32*28],data[7+32*28],data[8+32*28],data[9+32*28],data[10+32*28],data[11+32*28],data[12+32*28],data[13+32*28],data[14+32*28],data[17+32*28],data[18+32*28],  data[19+32*28],data[20+32*28],data[21+32*28],data[22+32*28],data[23+32*28],data[24+32*28],data[25+32*28],data[26+32*28],data[27+32*28],data[28+32*28],data[29+32*28],data[30+32*28],  data[28+32*0],data[28+32*15],data[28+32*16],data[31+32*28],
             data[1+32*29],data[2+32*29],data[3+32*29],data[4+32*29],data[5+32*29],data[6+32*29],data[7+32*29],data[8+32*29],data[9+32*29],data[10+32*29],data[11+32*29],data[12+32*29],data[13+32*29],data[14+32*29],data[17+32*29],data[18+32*29],  data[19+32*29],data[20+32*29],data[21+32*29],data[22+32*29],data[23+32*29],data[24+32*29],data[25+32*29],data[26+32*29],data[27+32*29],data[28+32*29],data[29+32*29],data[30+32*29],  data[29+32*0],data[29+32*15],data[29+32*16],data[31+32*29],
             data[1+32*30],data[2+32*30],data[3+32*30],data[4+32*30],data[5+32*30],data[6+32*30],data[7+32*30],data[8+32*30],data[9+32*30],data[10+32*30],data[11+32*30],data[12+32*30],data[13+32*30],data[14+32*30],data[17+32*30],data[18+32*30],  data[19+32*30],data[20+32*30],data[21+32*30],data[22+32*30],data[23+32*30],data[24+32*30],data[25+32*30],data[26+32*30],data[27+32*30],data[28+32*30],data[29+32*30],data[30+32*30],  data[30+32*0],data[30+32*15],data[30+32*16],data[31+32*30],

             data[0+32*1] ,data[0+32*2] ,data[0+32*3] ,data[0+32*4] ,data[0+32*5] ,data[0+32*6] ,data[0+32*7] ,data[0+32*8] ,data[0+32*9] ,data[0+32*10] ,data[0+32*11] ,data[0+32*12] ,data[0+32*13] ,data[0+32*14] ,data[0+32*17] ,data[0+32*18] ,  data[0+32*19] ,data[0+32*20] ,data[0+32*21] ,data[0+32*22] ,data[0+32*23] ,data[0+32*24] ,data[0+32*25] ,data[0+32*26] ,data[0 +32*27],data[0 +32*28],data[0 +32*29],data[0 +32*30],  data[0+32*0 ],data[15+32*0 ],data[16+32*0 ],data[31+32*0],
             data[1+32*15],data[2+32*15],data[3+32*15],data[4+32*15],data[5+32*15],data[6+32*15],data[7+32*15],data[8+32*15],data[9+32*15],data[10+32*15],data[15+32*11],data[12+32*15],data[13+32*15],data[14+32*15],data[15+32*17],data[15+32*18],  data[15+32*19],data[15+32*20],data[15+32*21],data[15+32*22],data[15+32*23],data[15+32*24],data[15+32*25],data[15+32*26],data[15+32*27],data[15+32*28],data[15+32*29],data[15+32*30],  data[0+32*15],data[15+32*15],data[16+32*15],data[31+32*15],
             data[1+32*16],data[2+32*16],data[3+32*16],data[4+32*16],data[5+32*16],data[6+32*16],data[7+32*16],data[8+32*16],data[9+32*16],data[10+32*16],data[11+32*16],data[12+32*16],data[13+32*16],data[14+32*16],data[16+32*17],data[16+32*18],  data[16+32*19],data[16+32*20],data[16+32*21],data[16+32*22],data[16+32*23],data[24+32*16],data[25+32*16],data[16+32*26],data[16+32*27],data[16+32*28],data[16+32*29],data[16+32*30],  data[0+32*16],data[15+32*16],data[16+32*16],data[31+32*16],
             data[1+32*31],data[2+32*31],data[3+32*31],data[4+32*31],data[5+32*31],data[6+32*31],data[7+32*31],data[8+32*31],data[9+32*31],data[10+32*31],data[11+32*31],data[12+32*31],data[13+32*31],data[14+32*31],data[17+32*31],data[18+32*31],  data[19+32*31],data[20+32*31],data[21+32*31],data[22+32*31],data[23+32*31],data[24+32*31],data[25+32*31],data[26+32*31],data[27+32*31],data[28+32*31],data[29+32*31],data[30+32*31],  data[0+32*31],data[15+32*31],data[16+32*31],data[31+32*31],
        };*/

        //This version ignores the things we expect to be 0, is is slightly faster, but still horribly slow
        myData={
                data[1+32*1] ,0            ,0            ,0            ,0            ,0            ,0            ,0            ,0            ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*2] ,data[2+32*2] ,0            ,0            ,0            ,0            ,0            ,0            ,0            ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*3] ,data[2+32*3] ,data[3+32*3] ,0            ,0            ,0            ,0            ,0            ,0            ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*4] ,data[2+32*4] ,data[3+32*4] ,data[4+32*4] ,0            ,0            ,0            ,0            ,0            ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*5] ,data[2+32*5] ,data[3+32*5] ,data[4+32*5] ,data[5+32*5] ,0            ,0            ,0            ,0            ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*6] ,data[2+32*6] ,data[3+32*6] ,data[4+32*6] ,data[5+32*6] ,data[6+32*6] ,0            ,0            ,0            ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*7] ,data[2+32*7] ,data[3+32*7] ,data[4+32*7] ,data[5+32*7] ,data[6+32*7] ,data[7+32*7] ,0            ,0            ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*8] ,data[2+32*8] ,data[3+32*8] ,data[4+32*8] ,data[5+32*8] ,data[6+32*8] ,data[7+32*8] ,data[8+32*8] ,0            ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*9] ,data[2+32*9] ,data[3+32*9] ,data[4+32*9] ,data[5+32*9] ,data[6+32*9] ,data[7+32*9] ,data[8+32*9] ,data[9+32*9] ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*10],data[2+32*10],data[3+32*10],data[4+32*10],data[5+32*10],data[6+32*10],data[7+32*10],data[8+32*10],data[9+32*10],data[10+32*10],0             ,0             ,0             ,0             ,0             ,0             ,
                data[1+32*11],data[2+32*11],data[3+32*11],data[4+32*11],data[5+32*11],data[6+32*11],data[7+32*11],data[8+32*11],data[9+32*11],data[10+32*11],data[11+32*11],0             ,0             ,0             ,0             ,0             ,
                data[1+32*12],data[2+32*12],data[3+32*12],data[4+32*12],data[5+32*12],data[6+32*12],data[7+32*12],data[8+32*12],data[9+32*12],data[10+32*12],data[11+32*12],data[12+32*12],0             ,0             ,0             ,0             ,
                data[1+32*13],data[2+32*13],data[3+32*13],data[4+32*13],data[5+32*13],data[6+32*13],data[7+32*13],data[8+32*13],data[9+32*13],data[10+32*13],data[11+32*13],data[12+32*13],data[13+32*13],0             ,0             ,0             ,
                data[1+32*14],data[2+32*14],data[3+32*14],data[4+32*14],data[5+32*14],data[6+32*14],data[7+32*14],data[8+32*14],data[9+32*14],data[10+32*14],data[11+32*14],data[12+32*14],data[13+32*14],data[14+32*14],0             ,0             ,
                //rows[0][17:30] rows[15][17:30] rows[16][17:30] normal column 31
                data[1+32*17],data[2+32*17],data[3+32*17],data[4+32*17],data[5+32*17],data[6+32*17],data[7+32*17],data[8+32*17],data[9+32*17],data[10+32*17],data[11+32*17],data[12+32*17],data[13+32*17],data[14+32*17],data[17+32*17],0             ,
                data[1+32*18],data[2+32*18],data[3+32*18],data[4+32*18],data[5+32*18],data[6+32*18],data[7+32*18],data[8+32*18],data[9+32*18],data[10+32*18],data[11+32*18],data[12+32*18],data[13+32*18],data[14+32*18],data[17+32*18],data[18+32*18],
                data[1+32*19],data[2+32*19],data[3+32*19],data[4+32*19],data[5+32*19],data[6+32*19],data[7+32*19],data[8+32*19],data[9+32*19],data[10+32*19],data[11+32*19],data[12+32*19],data[13+32*19],data[14+32*19],data[17+32*19],data[18+32*19],  data[19+32*19],0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*20],data[2+32*20],data[3+32*20],data[4+32*20],data[5+32*20],data[6+32*20],data[7+32*20],data[8+32*20],data[9+32*20],data[10+32*20],data[11+32*20],data[12+32*20],data[13+32*20],data[14+32*20],data[17+32*20],data[18+32*20],  data[19+32*20],data[20+32*20],0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*21],data[2+32*21],data[3+32*21],data[4+32*21],data[5+32*21],data[6+32*21],data[7+32*21],data[8+32*21],data[9+32*21],data[10+32*21],data[11+32*21],data[12+32*21],data[13+32*21],data[14+32*21],data[17+32*21],data[18+32*21],  data[19+32*21],data[20+32*21],data[21+32*21],0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*22],data[2+32*22],data[3+32*22],data[4+32*22],data[5+32*22],data[6+32*22],data[7+32*22],data[8+32*22],data[9+32*22],data[10+32*22],data[11+32*22],data[12+32*22],data[13+32*22],data[14+32*22],data[17+32*22],data[18+32*22],  data[19+32*22],data[20+32*22],data[21+32*22],data[22+32*22],0             ,0             ,0             ,0             ,0             ,0             ,0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*23],data[2+32*23],data[3+32*23],data[4+32*23],data[5+32*23],data[6+32*23],data[7+32*23],data[8+32*23],data[9+32*23],data[10+32*23],data[11+32*23],data[12+32*23],data[13+32*23],data[14+32*23],data[17+32*23],data[18+32*23],  data[19+32*23],data[20+32*23],data[21+32*23],data[22+32*23],data[23+32*23],0             ,0             ,0             ,0             ,0             ,0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*24],data[2+32*24],data[3+32*24],data[4+32*24],data[5+32*24],data[6+32*24],data[7+32*24],data[8+32*24],data[9+32*24],data[10+32*24],data[11+32*24],data[12+32*24],data[13+32*24],data[14+32*24],data[17+32*24],data[18+32*24],  data[19+32*24],data[20+32*24],data[21+32*24],data[22+32*24],data[23+32*24],data[24+32*24],0             ,0             ,0             ,0             ,0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*25],data[2+32*25],data[3+32*25],data[4+32*25],data[5+32*25],data[6+32*25],data[7+32*25],data[8+32*25],data[9+32*25],data[10+32*25],data[11+32*25],data[12+32*25],data[13+32*25],data[14+32*25],data[17+32*25],data[18+32*25],  data[19+32*25],data[20+32*25],data[21+32*25],data[22+32*25],data[23+32*25],data[24+32*25],data[25+32*25],0             ,0             ,0             ,0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*26],data[2+32*26],data[3+32*26],data[4+32*26],data[5+32*26],data[6+32*26],data[7+32*26],data[8+32*26],data[9+32*26],data[10+32*26],data[11+32*26],data[12+32*26],data[13+32*26],data[14+32*26],data[17+32*26],data[18+32*26],  data[19+32*26],data[20+32*26],data[21+32*26],data[22+32*26],data[23+32*26],data[24+32*26],data[25+32*26],data[26+32*26],0             ,0             ,0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*27],data[2+32*27],data[3+32*27],data[4+32*27],data[5+32*27],data[6+32*27],data[7+32*27],data[8+32*27],data[9+32*27],data[10+32*27],data[11+32*27],data[12+32*27],data[13+32*27],data[14+32*27],data[17+32*27],data[18+32*27],  data[19+32*27],data[20+32*27],data[21+32*27],data[22+32*27],data[23+32*27],data[24+32*27],data[25+32*27],data[26+32*27],data[27+32*27],0             ,0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*28],data[2+32*28],data[3+32*28],data[4+32*28],data[5+32*28],data[6+32*28],data[7+32*28],data[8+32*28],data[9+32*28],data[10+32*28],data[11+32*28],data[12+32*28],data[13+32*28],data[14+32*28],data[17+32*28],data[18+32*28],  data[19+32*28],data[20+32*28],data[21+32*28],data[22+32*28],data[23+32*28],data[24+32*28],data[25+32*28],data[26+32*28],data[27+32*28],data[28+32*28],0             ,0             ,  0             ,0             ,0             ,0             ,
                data[1+32*29],data[2+32*29],data[3+32*29],data[4+32*29],data[5+32*29],data[6+32*29],data[7+32*29],data[8+32*29],data[9+32*29],data[10+32*29],data[11+32*29],data[12+32*29],data[13+32*29],data[14+32*29],data[17+32*29],data[18+32*29],  data[19+32*29],data[20+32*29],data[21+32*29],data[22+32*29],data[23+32*29],data[24+32*29],data[25+32*29],data[26+32*29],data[27+32*29],data[28+32*29],data[29+32*29],0             ,  0             ,0             ,0             ,0             ,
                data[1+32*30],data[2+32*30],data[3+32*30],data[4+32*30],data[5+32*30],data[6+32*30],data[7+32*30],data[8+32*30],data[9+32*30],data[10+32*30],data[11+32*30],data[12+32*30],data[13+32*30],data[14+32*30],data[17+32*30],data[18+32*30],  data[19+32*30],data[20+32*30],data[21+32*30],data[22+32*30],data[23+32*30],data[24+32*30],data[25+32*30],data[26+32*30],data[27+32*30],data[28+32*30],data[29+32*30],data[30+32*30],  0             ,0             ,0             ,0             ,

                data[0+32*1] ,data[0+32*2] ,data[0+32*3] ,data[0+32*4] ,data[0+32*5] ,data[0+32*6] ,data[0+32*7] ,data[0+32*8] ,data[0+32*9] ,data[0+32*10] ,data[0+32*11] ,data[0+32*12] ,data[0+32*13] ,data[0+32*14] ,data[0+32*17] ,data[0+32*18] ,  data[0+32*19] ,data[0+32*20] ,data[0+32*21] ,data[0+32*22] ,data[0+32*23] ,data[0+32*24] ,data[0+32*25] ,data[0+32*26] ,data[0 +32*27],data[0 +32*28],data[0 +32*29],data[0 +32*30],  data[0+32*0 ] ,0             ,0             ,0             ,
                data[1+32*15],data[2+32*15],data[3+32*15],data[4+32*15],data[5+32*15],data[6+32*15],data[7+32*15],data[8+32*15],data[9+32*15],data[10+32*15],data[11+32*15],data[12+32*15],data[13+32*15],data[14+32*15],data[15+32*17],data[15+32*18],  data[15+32*19],data[15+32*20],data[15+32*21],data[15+32*22],data[15+32*23],data[15+32*24],data[15+32*25],data[15+32*26],data[15+32*27],data[15+32*28],data[15+32*29],data[15+32*30],  data[0+32*15] ,data[15+32*15],0             ,0             ,
                data[1+32*16],data[2+32*16],data[3+32*16],data[4+32*16],data[5+32*16],data[6+32*16],data[7+32*16],data[8+32*16],data[9+32*16],data[10+32*16],data[11+32*16],data[12+32*16],data[13+32*16],data[14+32*16],data[16+32*17],data[16+32*18],  data[16+32*19],data[16+32*20],data[16+32*21],data[16+32*22],data[16+32*23],data[16+32*24],data[16+32*25],data[16+32*26],data[16+32*27],data[16+32*28],data[16+32*29],data[16+32*30],  data[0+32*16] ,data[15+32*16],data[16+32*16],0             ,
                data[1+32*31],data[2+32*31],data[3+32*31],data[4+32*31],data[5+32*31],data[6+32*31],data[7+32*31],data[8+32*31],data[9+32*31],data[10+32*31],data[11+32*31],data[12+32*31],data[13+32*31],data[14+32*31],data[17+32*31],data[18+32*31],  data[19+32*31],data[20+32*31],data[21+32*31],data[22+32*31],data[23+32*31],data[24+32*31],data[25+32*31],data[26+32*31],data[27+32*31],data[28+32*31],data[29+32*31],data[30+32*31],  data[0+32*31] ,data[15+32*31],data[16+32*31],data[31+32*31],
        };

    }

    ///@brief The format string will be evaluated at compiletime, unfortunately declaring it as a variable does not work (the compiler doesn't recognize it as a constexpr), using a define is the most readable way of getting around it
#define printHex(ss,hex) ss<<std::format( (sizeof(T)==1 ? "{0:02x}," : (sizeof(T)==2 ? "{0:04x}," : (sizeof(T)==3 ? "{0:06x}," : "{0:08x},"))),myData[i++]);

    ///@brief convert the matrix to a string (includes 32 newline characters!)
    [[nodiscard]] std::string toString() const {
        std::stringstream ss;

        int i=0;
        for (int row = 0; row < 16; ++row) {
            for (int col = 0; col < 16; ++col) {
                printHex(ss,myData[i++]);
            }
            ss<<'\n';
        }
        ss<<'\n';
        for (int row = 16; row < 28; ++row) {
            for (int col = 0; col < 16; ++col) {
                printHex(ss,myData[i++]);
            }
            ss<<' ';
            for (int col = 16; col < 32; ++col) {
                printHex(ss,myData[i++]);
            }
            ss<<'\n';
        }
        ss<<'\n';
        for (int row = 28; row < 32; ++row) {
            for (int col = 0; col < 16; ++col) {
                printHex(ss,myData[i++]);
            }
            ss<<' ';
            for (int col = 16; col < 28; ++col) {
                printHex(ss,myData[i++]);
            }
            ss<<' ';
            for (int col = 28; col < 32; ++col) {
                printHex(ss,myData[i++]);
            }
            ss<<'\n';
        }

        return ss.str();
    }


#undef printHex

    ///@brief Constructor
    ///@warning for performance we do not check if the data is valid (has 0s in the right places), undefined behaviour may occur if the required 0s are not valid
    explicit valueMatrix_dense_3of4_backformat(std::array<T, 32 * 32-16*16> D): myData(D){};


    ///@brief compare a matrix of the same format to this matrix, assumes that the data in each is valid
    inline bool operator==(const valueMatrix_dense_3of4_backformat<T>& other) const
    {
        //Compare all the bits in the data
        return std::equal(myData.begin(),myData.end(),other.myData.begin());
    }
};