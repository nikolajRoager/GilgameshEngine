#include<iostream>
#include<chrono>
#include<array>
#include<string>
#include<map>
#include<set>
#include<bitset>

#include"immintrin.h"



//I only include the things i actually use, this is just a stupid habbit of mine
using std::cout, std::flush, std::array, std::string, std::map;

///@brief 128 bit register for position of each piece
//an std::array compiles to the same as uint8_t[16] which is much faster than using an std::vector
//it includes a copy and move assignment/constructor which makes it easier to use than uint8_t[16]
//My experiments suggest that the faster lookup from sorting the list is not worth the time it takes to sort
using piecelist = std::array<int8_t,16>;

//A list of moves, there can be at most 7 possible moves, I use an array large enough to fit all, and use another variable to keep track of how large the list is
//Using an array rather than an std::vector results in a 100 times speedup ... that is not an exageration, I went from 200 ns to 2 ns just by switching from vector
using moveList = std::array<piecelist,7>;

///@brief Convert a list of piece positions into a string we can print on a single line
string PiecelistToString(const piecelist& List)
{
    //I am NOT going to assume the list of pieces is ordered

    //A sorted list of counts at each position
    std::map<int8_t,int8_t> positions={};

    string Out="0123456789ABCDEF\n0000000000000000\n0000000000000000";
    for (int i = 1; i <8; i++)
    {
        //Increment the chars directly, it is ok, they 0 through 10 is in exactly the order you would expect
        ++Out[17+List[i]];
        ++Out[34+List[i+8]];
    }
    return Out;
}

/// @brief A baseline function for getting all legal moves from a piecelist format, without using AVX, the comments explain the algorithm quite well
/// @param roll What roll did we make, legal roles go from 0 to 4, but works fine with any roll
/// @param TestStatePiecelist The state we start with in the piecelist format, it is ASSUMED the player from byte 0 to 8 has turn, we DO NOT CHECK THE STATE BIT (Will not be modified), order of the pieces do not matter
/// @return Returns possible states, and prints the resulting state and average time-cost
void NoAVXPieceListStep(int8_t roll,const piecelist& state/*The state is NOT considered a legal workspace*/,moveList& out, int8_t& size)
{
    auto then = std::chrono::high_resolution_clock::now();

    int repeats = 10000000;
    for (int repeat = 0; repeat < repeats; ++repeat)
    {
        //The time to allocate this list should be counted
        size=0;

        if (roll!=0)
        {

            //For each piece of this player
            for (int8_t myPieceI = 1; myPieceI <8; ++myPieceI )
            {
                int newPosition=state[myPieceI]+roll;

                //We are in the middle of the board, where we and the enemy fight
                bool middlezone = newPosition>4 && newPosition<0xD;

                //Check if the new position is use
                bool blocked=false;
                int8_t take_enemy_piece_I=0xFF;

                if (newPosition>0xF)
                {
                    blocked=true;
                }
                else if (newPosition==0xF)
                {
                    //No problem, this is the finish
                }
                else//I did try to sort the piecelist, and use a binary search, but the performance was worse overall
                    for (int j = 1; j<8; ++j)
                    {
                        //we stand here already, in that case it is blocked
                        if (newPosition==state[j])
                        {
                            blocked=true;
                            break;
                        }
                        //the bad guy stands here check if we can take, ignore or be blocked by
                        else if (newPosition==state[j+8])
                        {
                            //We are in the middle part, where interactions happen
                            //If this is false, we can stand there fine
                            if (middlezone)
                            {
                                if (newPosition==8)//The central star blocks us if occupied by enemy
                                {
                                    blocked=true;
                                    break;
                                }
                                else//We can delete this enemy piece
                                {
                                    take_enemy_piece_I=j;
                                    break;
                                }
                            }
                        }
                    }
                //If this move is legal
                if (!blocked)
                {
                    out[size]=state;//Calls copy constructor, which behind ths scenes calls memcpy(newState.data(),state.data(), sizeof(state.data()))

                    out[size][myPieceI]=newPosition;
                    if (take_enemy_piece_I!=(int8_t)0xFF)
                    {
                        out[size][take_enemy_piece_I+8]=0;//Back you go
                    }
                    ++size;
                }
            }
        }
    }
    auto now = std::chrono::high_resolution_clock::now();

    cout<<"time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(now-then).count()/double(repeats)<<" nanoseconds\n";
    cout<<"Found "<<(int)size<<" options:\n";
    char optionId= 'a';
    for (int8_t i = 0; i < size; ++i)
    {
        cout<<"\tOption "<<optionId<<":\n";
        cout<<PiecelistToString(out[i])<<'\n';
        ++optionId;
    }
}

/// @brief Cast int64_t data to a string with bytes
/// @param state any integer data
/// @return string containing bytes are separated by space
string int64_t_to_string(const int64_t& state)
{
    string data(reinterpret_cast<const char*>(&state),sizeof(state));

    string Out="";
    bool first = true;
    int id=0;
    for (char& c : data)
    {
        if (id>0)
        {
            Out.push_back(' ');
        }
        ++id;
        //I don't think printing 0x in front is needed, it is pretty obviously hexadecimal
        //Out.append("0x");
        //Get the 4 bit numbers for the high and low bits, they are betwixt 0 and 16, and convert to a hexadecimal number
        char chigh = (c & 0xF0)>>4;
        if (chigh<10)
            Out.push_back('0'+chigh);
        else
            Out.push_back('A'+chigh-10);
        char clow = (c & 0x0F);
        if (clow <10)
            Out.push_back('0'+clow);
        else
            Out.push_back('A'+clow-10);
    }
    return Out;
}



/// @brief Cast __m256i data to a string with bytes.
/// @param state any integer data
/// @return string containing bytes are separated by space, 64 bit numbers are seperated by : and the 128 bit lanes are seperated by |
string avx256_to_string(const __m256i& state)
{
    string data(32,'a');
    _mm256_storeu_si256((__m256i*)data.data(),state);

    string Out="";
    bool first = true;
    int id=0;
    for (char& c : data)
    {
        if (id>0)
        {
            if (id%16==0)
                Out.append(" | ");//128 bit
            else if (id%8==0)
                Out.append(" : ");//64 bit
            else
                Out.push_back(' ');
        }
        ++id;
        //I don't think printing 0x in front is needed, it is pretty obviously hexadecimal
        //Out.append("0x");
        //Get the 4 bit numbers for the high and low bits, they are betwixt 0 and 16, and convert to a hexadecimal number
        char chigh = (c & 0xF0)>>4;
        if (chigh<10)
            Out.push_back('0'+chigh);
        else
            Out.push_back('A'+chigh-10);
        char clow = (c & 0x0F);
        if (clow <10)
            Out.push_back('0'+clow);
        else
            Out.push_back('A'+clow-10);
    }
    return Out;
}

/// @brief A function where I use AVX2 with 256 bit registers to check rolls in parallel
/// @param roll What roll did we make, legal roles go from 0 to 4, but works fine with any roll
/// @param TestStatePiecelist The state we start with in the piecelist format, it is ASSUMED the player from byte 0 to 8 has turn, we DO NOT CHECK THE STATE BIT (Will not be modified), order of the pieces do not matter
/// @return Returns possible states, and prints the resulting state and average time-cost
void PieceListStepAVX_256(int8_t roll,const piecelist& state/*The state is NOT considered a legal workspace*/,moveList& out, int8_t& size)
{

#define MY_PERMUTE_MASK(d, c, b, a) ((d << 6) | (c << 4) | (b << 2) | a)

    for (auto& O : out)
        O={};

    //Shift and rotate 1,2,3 or 4 bytes, these can be reused
    const __m256i ShiftRotate1234_register = _mm256_set_epi8(30,29,28,27,26,25,24,31, 21,20,19,18,17,16,23,22, 12,11,10,9,8,15,14,13, 3,2,1,0,7,6,5,4);
    const __m256i ShiftRotate4_register = _mm256_set_epi8(27,26,25,24,31,30,29,28, 19,18,17,16,23,22,21,20, 11,10,9,8,15,14,13,12, 3,2,1,0,7,6,5,4);

    //The location of the enemy pieces after the first and second shift+rotate for fast lookup, again reusable
    //I set the location of the enemy turn byte to 0, that way it will be ignored
    //Old lookup, with the address in the piecelist, kept for testing purposes
    //const __m256i enemy_lookup_0 = _mm256_set_epi8(14,13,12,11,10,9,0,15, 13,12,11,10,9,0,15,14, 12,11,10,9,0,15,14,13, 11,10,9,0,15,14,13,12);
    //const __m256i enemy_lookup_1 = _mm256_set_epi8(10,9,0,15,14,13,12,11, 9,0,15,14,13,12,11,10, 0,15,14,13,12,11,10,9, 15,14,13,12,11,10,9,0);

    //The location of the enemy pieces in BITS from the start of the byte 8 in the piecelist after the first and second shift+rotate for fast lookup, again reusable
    const __m256i enemy_lookup_0 = _mm256_set_epi8(48,40,32,24,16,8,0,56, 40,32,24,16,8,0,56,48, 32,24,16,8,0,56,48,40, 24,16,8,0,56,48,40,32);
    const __m256i enemy_lookup_1 = _mm256_set_epi8(16,8,0,56,48,40,32,24, 8,0,56,48,40,32,24,16, 0,56,48,40,32,24,16,8, 56,48,40,32,24,16,8,0);

    //Registers with constants we need for comparisons
    const __m256i all0 = _mm256_set1_epi8(0x00);
    const __m256i all4 = _mm256_set1_epi8(0x04);
    const __m256i allD = _mm256_set1_epi8(0x0D);
    const __m256i allF = _mm256_set1_epi8(0x0F);


    //A mask which only allows a single byte through, specifically picking out the first, second, third and fourth byte in my state or that of the enemy (the first is set aside for my state byte)
    const __m256i first4_mask = _mm256_set_epi8( 0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF , 0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF , 0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF , 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF);


//Uncomment to print every step of the algorithm
//#define VERBOSE

    auto then = std::chrono::high_resolution_clock::now();
    int repeats = 10000000;
#ifdef VERBOSE
//I am sure we don't want to see everything printed 0.1 million
    repeats=1;
#endif

        int64_t occupiedInts64[4];
        int64_t takenInts64[4];


    //A word of warning: there are a LOT of limited scopes below {code between curly brackets is a scope, variables are not visible outside},
    //This is because I only have 16 AVX2 registers, and 8 are already storing constants
    //And I NEED more than 16 registers in the algorithm!
    //By using scopes to limit the lifetime of some of my registers, the compiler will know which it can re-use
    //Really the compiler can do that all on its own, but I like to be explicit to make sure i do not accidentally ask for too many
    //I will try to define ALL the registries I use within each scope at the start of the scope, that way it is always clear how many are free

    //All of these are lists of 8 8-bit integers, repeated 4 times (because that makes the math faster)
    __m256i my_state_after_roll;//Where will I be if the roll is applied to this location in the piecelist
    __m256i AreOccupied;//FF for positions in the piecelist which are blocked
    __m256i WillTake;//If this move deletes an enemy piece, what is its ID (In the piecelist), 0 means we don't take anything
    __m256i my_old_state;//the piece-list data corresponding to me (plus at the end the byte which is 8, if the enemy is at 8)
    __m256i their_old_state;//the piece-list data corresponding to the enemy (ALSO including an 8 at the start, if the enemy is at 8)

    for (int repeat = 0; repeat < repeats; ++repeat)
    {
        size=0;

        //Pre positions FF on top of the turn bit, as that really shouldn't be there
        AreOccupied=_mm256_set_epi8(0xFF,0,0,0,0,0,0,0, 0xFF,0,0,0,0,0,0,0, 0xFF,0,0,0,0,0,0,0, 0xFF,0,0,0,0,0,0,0);

        //LIMITED SCOPE, temporary variables will not take up the registers for too long!
        //Load the old state, use it to set up the new state, and check for collisions with myself (or the enemy if they are at 8)
        //I think this uses 2 temporary registers
        {
            //Try to see if this is just as fast
            //int64_t my_old_state_single = *(reinterpret_cast<const int64_t*>(&state[1]));
            //int64_t new_state_single = my_old_state_single + roll*0x01010101;
            //__m256i my_new_state = _mm256_set1_epi64x(new_state_single);

            //reinterpret byte 1 to 8 as a 64 bits, in order to copy it four times(where my position is, plus the middle byte which tells us if they hav something at 8) as a single
            my_old_state = _mm256_set1_epi64x(*(reinterpret_cast<const int64_t*>(&state[1])));
            my_state_after_roll = _mm256_add_epi8(my_old_state,_mm256_set1_epi8(roll));
            __m256i temp_my_old_state=my_old_state;


#ifdef VERBOSE
            cout<<"old: "<<avx256_to_string(temp_my_old_state)<<'\n';
            cout<<"new: "<<avx256_to_string(my_state_after_roll)<<'\n';
#endif
            //To do parallel checks, we will shift each 64 bits 1,2,3 or 4 bytes left
            temp_my_old_state = _mm256_shuffle_epi8(temp_my_old_state,ShiftRotate1234_register);
#ifdef VERBOSE
            cout<<"<<1: "<<avx256_to_string(temp_my_old_state)<<'\n';
#endif
            AreOccupied = _mm256_or_si256(AreOccupied,_mm256_cmpgt_epi8(my_state_after_roll,allF));

            //Mask to tell us if these things are occupied, it is so if the new state is equal to the old state, which has been shifted around to compare all
            //We are going to need to do this 7 different times, since we can compare 256 bits at the time, it takes only 2 registers
            AreOccupied = _mm256_or_si256(AreOccupied,_mm256_cmpeq_epi8(temp_my_old_state,my_state_after_roll));

            //Shift another 4 bytes, which creates the last 3 states to compare to
            temp_my_old_state = _mm256_shuffle_epi8(temp_my_old_state,ShiftRotate4_register);

            //AreOccupied now contains 0xFF if it is occupied by one of my pieces (or the other )
            AreOccupied = _mm256_or_si256(AreOccupied,_mm256_cmpeq_epi8(temp_my_old_state,my_state_after_roll));

#ifdef VERBOSE
            cout<<"<<1: "<<avx256_to_string(temp_my_old_state)<<'\n';
#endif
        }
#ifdef VERBOSE
        cout<<"occ: "<<avx256_to_string(AreOccupied)<<'\n';
#endif


        //LIMITED SCOPE, temporary variables will not take up the registers for too long!
        //I think this scope uses 2 simulataneous temporary registers
        {

            //Now we should check for enemy pieces at the same position as us,
            their_old_state = _mm256_set1_epi64x(*(reinterpret_cast<const int64_t*>(&state[8])));//This also catches the 08 or 00 at the start, it will be disregarded

            //(but only if it is on 5, D or anything between, where collision is turned on)
#ifdef VERBOSE
            cout<<"their: "<<avx256_to_string(their_old_state)<<'\n';
#endif
            __m256i mask = _mm256_cmpgt_epi8(their_old_state,all4);
            __m256i their_state_4toD= _mm256_and_si256(their_old_state,mask);
            mask = _mm256_cmpgt_epi8(allD,their_state_4toD);

            //Now, their_old_state has 0s everywhere where collision is turned of, and my_new_State doesn't ever have any 0s so it is fine
            their_state_4toD= _mm256_and_si256(their_state_4toD,mask);


#ifdef VERBOSE
            cout<<"their: "<<avx256_to_string(their_state_4toD)<<'\n';
            cout<<"mine : "<<avx256_to_string(my_state_after_roll)<<'\n';
#endif

            //Now do the same trick to find the mask of my new pieces, which intersect enemy pieces:

            //To do parallel checks, we will shift each 64 bits 1,2,3 or 4 bytes left
            their_state_4toD = _mm256_shuffle_epi8(their_state_4toD,ShiftRotate1234_register);
#ifdef VERBOSE
            cout<<"<<1  : "<<avx256_to_string(their_state_4toD)<<'\n';
#endif
            //FF when there is an enemy there
            WillTake= _mm256_cmpeq_epi8(their_state_4toD,my_state_after_roll);

            //AND with the bits in the enemy lookup register, that way the mask will contain the location in the enemies piecelist
            WillTake=_mm256_and_si256(WillTake,enemy_lookup_0);

            //Shift another 4 bytes, which creates the last 3 states to compare to
            their_state_4toD= _mm256_shuffle_epi8(their_state_4toD,ShiftRotate4_register);

            //FF when an enemy piece is there
            __m256i nextWillTake = _mm256_cmpeq_epi8(their_state_4toD,my_state_after_roll);
            //Use the new lookup table
            nextWillTake=_mm256_and_si256(nextWillTake,enemy_lookup_1);

            //Then and the bits together
            WillTake= _mm256_or_si256(WillTake,nextWillTake);

#ifdef VERBOSE
            cout<<"<<1  : "<<avx256_to_string(their_state_4toD)<<'\n';
            cout<<"take : "<<avx256_to_string(WillTake)<<'\n';
#endif
        }
        //Now, the taken and blocked bytes are split in four pieces, for the next calculation, we would like 4 identical copies


        //These 4 permutations are SLOW, easilly taking as long as EVERYTHING above, still,
        //it is faster than copying everything back into 4 int64_t

        //First flip the bytes in the lanes                        //Unchanged is is MY_PERMUTE_MASK(3,2,1,0)
        AreOccupied=_mm256_or_si256(AreOccupied,_mm256_permute4x64_epi64(AreOccupied,MY_PERMUTE_MASK(2,3,0,1)));
        //Then copy accross the lanes
        AreOccupied=_mm256_or_si256(AreOccupied,_mm256_permute4x64_epi64(AreOccupied,MY_PERMUTE_MASK(1,0,3,2)));
        //Do the same with those we should take
        //FLip
        WillTake=_mm256_or_si256(WillTake,_mm256_permute4x64_epi64(WillTake,MY_PERMUTE_MASK(2,3,0,1)));
        //Cross
        WillTake=_mm256_or_si256(WillTake,_mm256_permute4x64_epi64(WillTake,MY_PERMUTE_MASK(1,0,3,2)));

        //NOW all there is left to do is read of the states, Here is a version which DOESN'T use further AVX functions to do this:
/*
    int8_t Occupieds [32];
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(&Occupieds[0]),AreOccupied);
    int8_t Takable[32];
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(&Takable[0]),WillTake);
    //_mm256_storeu_si256(reinterpret_cast<__m256i*>(&takenInts64[0]),WillTake);

    size=0;
    for (int8_t i = 0; i < 7; ++i)
        if (Occupieds[i]!=(int8_t)0xFF)
            ++size;
    //NewList=vector<piecelist>(size);


    //This version DOES NOT FLIP TURN BIT, OR UPDATE 8-BIT
    for (int8_t i = 0; i < 7; ++i)
    {
            if (Occupieds[i]!=(int8_t)0xFF)
            {
#ifdef VERBOSE
                cout<<"Move from "<<(int)i<<"'th"<<'\n';
#endif
                //We are gonna have a new state
                out[size]=state;//Calls copy constructor, which behind ths scenes calls memcpy(newState.data(),state.data(), sizeof(state.data()))
                int8_t old = out[size][i+1];
                out[size][i+1]+=roll;

                if (old==8)//Unmark 8, keep turn half-byte
                    out[size][0]&=0xF0;
                else if ( out[size][i+1]==8 )//This is special, we don't flip turn half-byte, but we mark us as at 8
                    out[size][0]|=0x08;
                else if (out[size][i+1]==4 || out[size][i+1]==(int8_t)0xE)
                {
                    //Do not flip turn half-byte of me or the enemy, keep it as it is (my turn still)
                }
                else//set state byte to 0 for me
                {
                    out[size][0]&=0x0F;
                    out[size][8]|=0xF0;//Set state half-byte for them,
                }


                if (Takable[i]!=0)
                {
                    out[size][Takable[i]]=0;//Back you go
    #ifdef VERBOSE
                    cout<<"\tMurder "<<(int)Takable[i]<<"'th"<<'\n';
    #endif
                }
                ++size;
            }
    }
*/

        {


        //Now we need to count the number of legal moves (0x00 bytes in AreOccupied)
        //and we need to re-arrange my old and new state, so the legal moves come first
        //(so the first size bytes correspond to pieces which can be moved, and the rest pieces which can not)
        //Alas, we need to loop through all the states individually, so no AVX2 magic here
        size=0;
        int8_t ShuffleMaskArray[8];

        //It is done using a manually unrolled for-loop
        //Manually unrolled for loop, since _mm256_extract_epi8 expects constant expressions

        //The code below is a manually unrolled for-loop (since the intrinsics require compile-time constants!), this is what it would look like without unrolling:
        /*
        Loop through the 7 pieces we can move
        for (int i = 0; i<7; ++i)
        {
            //if AreOccupied is not 0x00, the move is not allowed
            if (_mm256_extract_epi8(AreOccupied,i))
                ShuffleMask[7-i+size]=i;//In that case add i to the end of the list
            else
                ShuffleMask[1+size++]=i;//build the legal moves up from the other end (leave the first byte unused, we are going to want my state bit there)
        }
        */

       //After some testing, the fastest proved to be manually unrolling the loop, and using movemask to extract the information as a 32 bit integer
        int occupied32=_mm256_movemask_epi8(AreOccupied);

        if (occupied32 & 1<<0)//Check byte 0, 1, 2 etc
            ShuffleMaskArray[7]=0;
        else
            ShuffleMaskArray[++size]=0;
        if (occupied32 & 1<<1)//I expect the compiler to do the shifts at compiletime
            ShuffleMaskArray[6+size]=1;
        else
            ShuffleMaskArray[++size]=1;
        if (occupied32 & 1<<2)
            ShuffleMaskArray[5+size]=2;
        else
            ShuffleMaskArray[++size]=2;
        if (occupied32 & 1<<3)
            ShuffleMaskArray[4+size]=3;
        else
            ShuffleMaskArray[++size]=3;
        if (occupied32 & 1<<4)
            ShuffleMaskArray[3+size]=4;
        else
            ShuffleMaskArray[++size]=4;
        if (occupied32 & 1<<5)
            ShuffleMaskArray[2+size]=5;
        else
            ShuffleMaskArray[++size]=5;
        if (occupied32 & 1<<6)
            ShuffleMaskArray[1+size]=6;
        else
            ShuffleMaskArray[++size]=6;
        ShuffleMaskArray[0]=0xFF;//Sets my state byte to 0x00


        __m256i ShuffleMask= _mm256_set1_epi64x(*reinterpret_cast<int64_t*>(&ShuffleMaskArray[0]));
#ifdef VERBOSE
            cout<<"Before shuffle\n";
            cout<<"occupied mask   :"<<avx256_to_string(AreOccupied)<<'\n';
            cout<<"shuffle mask    :"<<avx256_to_string(ShuffleMask)<<'\n';
            cout<<"mine before move:"<<avx256_to_string(my_old_state)<<'\n';
            cout<<"mine after move :"<<avx256_to_string(my_state_after_roll)<<'\n';
            cout<<"take pieces?    :"<<avx256_to_string(WillTake)<<'\n';
#endif
        my_old_state=_mm256_shuffle_epi8(my_old_state,ShuffleMask);
        my_state_after_roll=_mm256_shuffle_epi8(my_state_after_roll,ShuffleMask);
        WillTake=_mm256_shuffle_epi8(WillTake,ShuffleMask);
        //We are going to need a mask of the legal moves anyway, and we might as well make it like this:
        AreOccupied=_mm256_shuffle_epi8(AreOccupied,ShuffleMask);

#ifdef VERBOSE
            cout<<"After shuffle\n";
            cout<<"occupied mask   :"<<avx256_to_string(AreOccupied)<<'\n';
            cout<<"mine before move:"<<avx256_to_string(my_old_state)<<'\n';
            cout<<"mine after move :"<<avx256_to_string(my_state_after_roll)<<'\n';
            cout<<"take pieces?    :"<<avx256_to_string(WillTake)<<'\n';
#endif
        }

        //if there are legal moves, we should generate them
        if (size>0)
        {
            {
                //We are first going to generate the first 4 legal moves, first for me
                __m256i mine_new4= _mm256_blendv_epi8(my_state_after_roll,my_old_state,first4_mask);
                __m256i their_new4;
                {//Tell the compiler that this temporary thing can be discarded safely
                //then get the address in each of the 4 moves, which we should set to 0, the address is at byte 0,1,2,3
                __m256i addressToSetTo0 = _mm256_andnot_si256(first4_mask,WillTake);
                //move it to byte 0, that means the entire 64 bit block is EQUAL to the address, which in our lookup table is the number of BITS from the start the enemy piece we want to take is
                addressToSetTo0 = _mm256_srlv_epi64(addressToSetTo0,_mm256_set_epi64x(16,24,32,40));
                //Now move the number of bytes back by itself, this means the byte in addressToSetTo0 is non-zero in the same location as the byte in their state we want to set to 0
                addressToSetTo0 = _mm256_sllv_epi64(addressToSetTo0,addressToSetTo0);
                //Simply set that byte to 0!, done, with all 4, simultaneously! WE DID IT (for the first 4 states, if there are more we will have to deal with them)
                their_new4=_mm256_andnot_si256(_mm256_cmpgt_epi8(addressToSetTo0,all0),their_old_state);

#ifdef VERBOSE
                cout<<"Applying first 4 moves\n";
                cout<<"mine before roll   :"<<avx256_to_string(my_old_state)<<'\n';
                cout<<"mine after roll    :"<<avx256_to_string(my_state_after_roll)<<'\n';
                cout<<"My state after move:"<<avx256_to_string(mine_new4)<<'\n';

                cout<<"their before move  :"<<avx256_to_string(their_old_state)<<'\n';
                cout<<"their address to 0 :"<<avx256_to_string(addressToSetTo0 )<<'\n';
                cout<<"their after move   :"<<avx256_to_string(their_new4)<<'\n';

                int64_t Test [4];
                _mm256_storeu_si256((__m256i*)&Test,addressToSetTo0);
                cout<<"extracted "<<Test[0]<<' '<<Test[1]<<' '<<Test[2]<<' '<<Test[3]<<'\n';
#endif
                }
                //Ok I lied, we still need to extract the data ... and there is a problem: the order of the data is wrong!
                //We have 4 blocks of 64 bytes where the Last seven are my state in each move
                //the first byte is the enemies state-byte, which we need to replace with our state-byte
                //We also have 4 blocks of 64 bytes where the first is the enemy state-byte, and the next 7 are enemy locations
                //Let us quickly interleave these things before performing expensive memcpy:

#ifdef VERBOSE
                cout<<"My state before interleave:"<<avx256_to_string(mine_new4)<<'\n';
                cout<<"their before interleave   :"<<avx256_to_string(their_new4)<<'\n';
#endif
                //First make it so they fit together
                mine_new4=_mm256_permute4x64_epi64(mine_new4,MY_PERMUTE_MASK (3,1,2,0));
                their_new4=_mm256_permute4x64_epi64(their_new4,MY_PERMUTE_MASK(1,3,0,2));
                __m256i select0101 = _mm256_set_epi64x(0x0,0xFFFFFFFFFFFFFFFF,0x0,0xFFFFFFFFFFFFFFFF);
                //Now mask out state 0 and 1, this now contains the bytes corresponding to the first and second move
                __m256i FirstTwoStates = _mm256_blendv_epi8(their_new4,mine_new4,select0101);

                //And this contains the ones for move three and four in wrong order
                __m256i SecondTwoStates = _mm256_blendv_epi8(mine_new4,their_new4,select0101);
                //TBD, can we change this
                SecondTwoStates=_mm256_permute4x64_epi64(SecondTwoStates,MY_PERMUTE_MASK(2,3,0,1));
                //Now the two states contain the data of four moves, copy it into the output,
                //if size is less than 4, it does include some garbage data, but that doesn't matter
                _mm256_storeu_si256(reinterpret_cast<__m256i*>(&out[0]),FirstTwoStates);
                _mm256_storeu_si256(reinterpret_cast<__m256i*>(&out[2]),SecondTwoStates);
#ifdef VERBOSE
                cout<<"My state after interleave :"<<avx256_to_string(mine_new4)<<'\n';
                cout<<"their after interleave    :"<<avx256_to_string(their_new4)<<'\n';
                cout<<"Move 0 and 1              :"<<avx256_to_string(FirstTwoStates)<<'\n';
                cout<<"Move 2 and 3              :"<<avx256_to_string(SecondTwoStates)<<'\n';
#endif

            }

            //Ok, we need to do it again
            if (size>4)
            {
                //TEMP fix
                throw std::runtime_error("NOT IMPLEMENTED FOR LARGER SIZE");
            }
        }
    }
    auto now = std::chrono::high_resolution_clock::now();

    _mm256_storeu_si256(reinterpret_cast<__m256i*>(&occupiedInts64[0]),AreOccupied);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(&takenInts64[0]),WillTake);
    occupiedInts64[0]=occupiedInts64[0]|occupiedInts64[1]|occupiedInts64[2]|occupiedInts64[3];
    takenInts64[0]=takenInts64[0]|takenInts64[1]|takenInts64[2]|takenInts64[3];

    cout<<"occ : "<<int64_t_to_string(occupiedInts64[0])<<'\n';
    cout<<"take: "<<int64_t_to_string(takenInts64[0])<<'\n';
    cout<<"time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(now-then).count()/double(repeats)<<" nanoseconds\n";
    cout<<"Found "<<(int)size<<" options:\n";
    char optionId= 'a';
    for (int8_t i = 0; i < size; ++i)
    {
        cout<<"\tOption "<<optionId<<":\n";
        cout<<PiecelistToString(out[i])<<'\n';
        ++optionId;
    }

//Ok, we don't need it any more
#undef MY_PERMUTE_MASK
}


int main()
{
//I am using some bit-wise trickery to speed up calculations, it only works on little-endian systems
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
//Ok, i trust this
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #error "System uses big-endian byte order, this program requires little endian systems!"
//#elif defined(_MSC_VER) MSVC only officially supports little-endian systems, so we could trust it ... but I don't, so we check that too
#else
//runtime check just to be sure
int32_t number = 0x1;
if(*reinterpret_cast<uint8_t*>(&number) != 0x1)
{
    cout<<"System uses big-endian byte order, this program requires little endian systems!"<<std::endl;
    return 1;
}
#endif

    //The first and eigth byte indicate whose turn it is, if it is 0xF0 or 0xF8 it is this players turn, if 0x00 or 0x08 it is not. It ends with 8 if this player occupies position 8
    //Then 7 bytes for player 0s pieces location, and 7 for player1s
    piecelist TestStatePiecelist=//128 bits
    {
        //The (int8_t) are there to silence compiler warnings
        (int8_t)0xF0,//Player 0 turn
        (int8_t)0x0,(int8_t)0x0,(int8_t)0x3,(int8_t)0x4,(int8_t)0xD,(int8_t)0x6,(int8_t)0xE,
        (int8_t)0x08,//Either 08 or 00, will be 8 if the other one has anything at 8
        (int8_t)0x0,(int8_t)0x1,(int8_t)0x2,(int8_t)0x3,(int8_t)0x5,(int8_t)0x8,(int8_t)0xF,
    };

    int8_t roll = 2;//Player 0 has rolled a 2, legal moves include 0->2, 3->5 (take player 1), 9->0xB
    cout<<"START PROGRAM\n\n";
    cout<<"Rolled "<<(int)roll<<" Example state:\n";
    cout<<PiecelistToString(TestStatePiecelist)<<'\n';
    cout<<"Step with Piece List without AVX\n";

    moveList Moves;
    int8_t size=0;
    NoAVXPieceListStep(roll,TestStatePiecelist,Moves,size);
    {
        cout<<"\nStep with Piece list, with AVX 256\n";
        PieceListStepAVX_256(roll,TestStatePiecelist,Moves,size);
    }
/*
    //Some byte data
    int8_t bytes[8] = {0,0,0x0D,0,0,0,0,0};

    //Cast bytes to an int64_t
    int64_t integer = *(reinterpret_cast<int64_t*>(&bytes[0]));

    std::cout<<integer<<std::endl;//Prints 851968

    integer = integer>>2*8;//Shift bytes
    //Copy back
    memcpy(&bytes ,&integer,sizeof(integer));

    std::cout<<integer<<std::endl;//Prints 13
    for (int8_t b : bytes)
        std::cout<<(int)b<<' ';
    std::cout<<std::endl;//Prints 13, 0, 0, 0, 0, 0, 0, 0
*/
/*
    //I have manually verified that this reference is right, so let us check against it
    //No need to make it efficient
    auto verify = [&reference](const vector<piecelist>& options)
    {
        //We need to verify that each of the options is in the reference list at least once
        //We will ignore dublicates in reference or options as that really doesn't matter

        return true;
    };
*/
    cout<<flush;
    return 0;
}
