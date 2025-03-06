//
// Created by nikolaj on 18/02/25.
//

#include <cstdint>
#include <array>
#include <format>
#include <sstream>
#include <string>

#pragma once

///@brief dense square matrix of AI values, full matrix even the blocks which are guaranteed to be 0, in ordered format, weere column and row i 0 to 15 correspond to player 0 having a piece at position i, i from 16 to 31 correspond to player 1 having a piece at position i-16
///@brief Value matrices are from the perspective of player 0, and assumes that it is player 1s turn!
///@brief int8_t has the advantage that everything can fit in a single avx registry, but AVX2 doesn't support as many 8-bit operations as 16 bit
///@warning it is assumed in the algorithms that the matrices not contain larger numbers than could be stored in an 8-bit version, the larger matrices are only there to speed up calculations, by saving on casting time. UNDEFINED BEHAVIOUR may occur if that is not so
template<typename T, typename =std::enable_if<std::is_integral_v<T>>>
class valueMatrix_dense_full
{

protected:
///@brief dense square matrix of AI values, in ordered format, where column and row i 0 to 15 correspond to player 0 having a piece at position i, i from 16 to 31 correspond to player 1 having a piece at position i-16
std::array<T,32*32> myData=
        {
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
    ///@brief Constructor
    ///@warning for performance we do not check if the data is valid (has 0s in the right places), undefined behaviour may occur if the required 0s are not valid
    explicit valueMatrix_dense_full(std::array<T, 32 * 32> D): myData(D){};


    ///@brief Template constructor from another matrix with same signedness, which we must scale up or down
    ///@warning for performance we do not check if the data is valid (has 0s in the right places), undefined behaviour may occur if the required 0s are not valid
    template<typename U,
            typename =std::enable_if<
                        std::is_integral_v<U>/*redundant, but I like to write it explicitly*/
                        && std::is_signed_v<U> == std::is_signed_v<T>//Same signedness required
                    >
            > explicit valueMatrix_dense_full(const valueMatrix_dense_full<U>& data)
    {
        for (int i =0; i <data.getData().size(); ++i)
        {
            //I just assume the other matrix has 0s at the required places
            myData[i]=static_cast<T>(data.getData()[i]);
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

    ///@brief Simply get the data at this index, modifiable (undefined behaviour if you modify a required 0)
    inline T& operator[](int index)
    {
        return myData[index];
    }
    inline const T& operator[](int index) const
    {
        return myData[index];
    }


    ///@brief convert the matrix to a string (includes 32 newline characters!)
    [[nodiscard]] std::string toString() const {
        std::stringstream ss;

    ///@brief The format string will be evaluated at compiletime, unfortunately declaring it as a variable does not work (the compiler doesn't recognize it as a constexpr), using a define is the most readable way of getting around it
#define printHex(ss,hex) ss<<std::format( (sizeof(T)==1 ? "{0:02x}," : (sizeof(T)==2 ? "{0:04x}," : (sizeof(T)==3 ? "{0:06x}," : "{0:08x},"))),myData[i++]);

        int i=0;
        for (int row = 0; row < 16; ++row) {
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
        for (int row = 16; row < 32; ++row) {
            for (int col = 0; col < 16; ++col) {
                printHex(ss,myData[i++]);
            }
            ss<<' ';
            for (int col = 16; col < 32; ++col) {
                printHex(ss,myData[i++]);
            }
            ss<<'\n';
        }
        //Let's just clean it up, it was just a thing I did to make this function more readable
#undef printHex

        return ss.str();
    }

    ///@brief compare a matrix of the same format to this matrix, assumes that the data in each is valid
    inline bool operator==(const valueMatrix_dense_full<T>& other) const
    {
        //Compare all the bits in the data
        return std::equal(myData.begin(),myData.end(),other.myData.begin());
    }

};