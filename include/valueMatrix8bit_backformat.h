//
// Created by nikolaj on 18/02/25.
//

#include <cstdint>
#include <array>

#ifndef GILGAMESHENGINE_MAT8BIT_H
#define GILGAMESHENGINE_MAT8BIT_H

#endif //GILGAMESHENGINE_MAT8BIT_H

///@brief 8 bit dense square matrix of AI values, in counters-in-the-back format, please open the valueMatrix8bit_backformat.h file to see a diagram
class valueMatrix8bit_backformat
{

    ///@brief 8 bit dense square matrix of AI values, although the matrix is lower-triangular this version includes all data (simplifying lookup), backformat means that the values associated with unstarted and finished counts are in the back, please open the valueMatrix8bit_backformat.h file to see a diagram
    std::array<int8_t,32*32+33> data=
            //Let me try to explain the structure of the matrix in memory, and why it allows me to simplify many calculations
            //This works best if the lines are not wrapping around
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
//      | | | | | | | | | | | | | |  | |     | | | | | | | | | | | |  | | | |  column 33 would contain the player turn bit, but since it would all be 0 until the last row, I leave it out
//      v v v v v v v v v v v v v v  v v     v v v v v v v v v v v v  v v v v  v //Similarly the top 14 columns get selected, if player 0 has a piece at #
        1,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-1
        1,1,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-2
        1,1,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-3
        1,1,1,1,0,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-4
        1,1,1,1,1,0,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-5
        1,1,1,1,1,1,0,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-6
        1,1,1,1,1,1,1,0,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-7
        1,1,1,1,1,1,1,1,0,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-8
        1,1,1,1,1,1,1,1,1,0,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-9
        1,1,1,1,1,1,1,1,1,1,0,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-A
        1,1,1,1,1,1,1,1,1,1,1,0,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-B
        1,1,1,1,1,1,1,1,1,1,1,1,0,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-C
        1,1,1,1,1,1,1,1,1,1,1,1,1,0, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-D
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,0,//  0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,  0//<-E
        //Block E                    Block F  Block G               Block H //And these get selected if player 1 is at #
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,0,    0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//0//<-1
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//0//<-2
        //Block I                    Block J  Block K               Block L
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//0<-3
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,//0<-4
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,0,0,0,0,0,0,0,0,0, 0,0,0,0,//0<-5
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,0,0,0,0,0,0,0,0, 0,0,0,0,//0<-6
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,0,0,0,0,0,0,0, 0,0,0,0,//0<-7
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,0,0,0,0,0,0, 0,0,0,0,//0<-8
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,0,0,0,0,0, 0,0,0,0,//0<-9
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,0,0,0,0, 0,0,0,0,//0<-A
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,0,0,0, 0,0,0,0,//0<-B
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,0,0, 0,0,0,0,//0<-C
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,0, 0,0,0,0,//0<-D
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,//0<-E
        //Block M                    Block O  Block P               Block Q     And the final 4 get multiplied by:
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 1,0,0,0,//0<-0 unstarted
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 1,1,0,0,//0<-0 finished
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,0,//0<-1 unstarted
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,//0<-1 finished

        //Block R, the player whose turn it is multiplied with every single piece, the very last number is always there, if the turn bit is set
        1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,    1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,  1

        //The most logical way to divide up the matrix, would be block A (player 0 0), Blocks B+C+E+F (plyer 0 1, which IS all 0 and can be skipped), Block I+J (Player 1 0) and Block K+L (player 1 1) and finally block M (player 0 and unstarted/finished of both) block O+P (player 1 and unstarted/finished) and finally Block Q (unstarted/finished and unstarted/finished); (Blocks D, H, and L are all 0 and need not be considered)

        //However we need 256 bit per register, so with this matrix, it is more logical to look at the matrix using the blocks: A+B+E+F, skip C+D+G+H, look at I+J, K+L, M+O, and P+Q, and finally R
            };

public:
    ////@brief address of the 14-16 byte (256 bit) rows which contains player0's value matrix interaction with themself, and player 1s pieces at position 1,2:
    [[nodiscard]] inline const int8_t* blockABaddress() const {
        return &(data[0]);
    }

    ////@brief address of the 14-32 byte (512 bit) rows The first 14 bytes contain player 0's interaction with player 1, the next are player 1's interaction with itself, the final 4 are always 0
    [[nodiscard]] inline const int8_t* blockEFGHIJKLaddress() const {
        return &(data[256]);
    }

    ////@brief address of the 4-32 byte (512 bit) rows.  representing the interaction with the number of started and unstarted pieces with player 0 and 1's position
    [[nodiscard]] inline const int8_t* blockMOPQLaddress() const {
        return &(data[256]);
    }

    ////@brief address of the 33 byte (520 bit) row, with
    [[nodiscard]] inline const int8_t* blockRaddress() const {
        return &(data[256]);
    }
};