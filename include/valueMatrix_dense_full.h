//
// Created by nikolaj on 18/02/25.
//

#include <cstdint>
#include <array>

#pragma once

///@brief dense square matrix of AI values, full matrix even the blocks which are guaranteed to be 0, in ordered format, weere column and row i 0 to 15 correspond to player 0 having a piece at position i, i from 16 to 31 correspond to player 1 having a piece at position i-16
///@brief Value matrices are from the perspective of player 0, and assumes that it is player 1s turn!
///@brief int8_t has the advantage that everything can fit in a single avx registry, but AVX2 doesn't support as many 8-bit operations as 16 bit
template<typename T, typename =std::enable_if<std::is_integral_v<T>>>
class valueMatrix_dense_full
{

protected:
///@brief dense square matrix of AI values, in ordered format, where column and row i 0 to 15 correspond to player 0 having a piece at position i, i from 16 to 31 correspond to player 1 having a piece at position i-16
std::array<T,32*32> myData=
        {
        //The default data below only illustrate the data structure, the matrix can NOT be default initialized
        //0's below indicate data which must be 0, 1's below indicate data which can be any 8 bit integer
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-0 Player 0
1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-1
1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-2
1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-3
1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-4
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-5
1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-6
1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-7
1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-8
1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-9
1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-A
1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-B
1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-C
1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-D
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-E
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-F

1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-0 Player 1
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-1
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,//0<-2
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,//0<-3
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,//0<-4
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,//0<-5
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,//0<-6
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,//0<-7
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,//0<-8
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,//0<-9
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,//0<-A
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,//0<-B
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,//0<-C
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,//0<-D
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,//0<-E
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//0<-F
        };
public:

    const std::array<T,32*32>& getData()const
    {
        return myData;
    }
    explicit valueMatrix_dense_full(std::array<T, 32 * 32> D): myData(D){};


    ///@brief Template constructor from another matrix, which we must scale up or down
    template<typename U> valueMatrix_dense_full(const valueMatrix_dense_full<U>& data)
    {
        myData={0};
        for (int i =0; i <data.getData().size(); ++i)
        {
            myData[i]=static_cast<U>(data.getData()[i]);
        }
    }


    ////@brief address of the start of the data
    [[nodiscard]] inline const void* data() const {
        return &(myData[0]);
    }
    ///@brief size of data in bytes
    [[nodiscard]] inline auto byteSize()const{return myData.size()*sizeof (T);}


    ////@brief address of the 14-16 byte (256 bit) rows which contains player0's value matrix interaction with themself, and player 1s pieces at position 1,2:
    [[nodiscard]] inline const T* blockABaddress() const {
        return &(myData[0]);
    }

    ////@brief address of the 14-32 byte (512 bit) rows The first 14 bytes contain player 0's interaction with player 1, the next are player 1's interaction with itself, the final 4 are always 0
    [[nodiscard]] inline const T* blockEFGHIJKLaddress() const {
        return &(myData[256]);
    }

    ////@brief address of the 4-32 byte (512 bit) rows.  representing the interaction with the number of started and unstarted pieces with player 0 and 1's position
    [[nodiscard]] inline const T* blockMOPQLaddress() const {
        return &(myData[256]);
    }

    ////@brief address of the 33 byte (520 bit) row, with
    [[nodiscard]] inline const T* blockRaddress() const {
        return &(myData[256]);
    }

    ///@brief Simply get the data at this index
    inline T operator[](int index)
    {
        return myData[index];
    }
};