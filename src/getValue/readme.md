Get value Algorithms
====================

This folder contains different implementations of the getValue function, defined in `include/getValue.h`
'

All files in this folder are automatically compiled, and included in the speed test

The file constant.cpp literally just returns 0, it is only used as a baseline for the speed test.

The names of all the other files indicate the formats, extension, and algorithms used; they are written in camelCase with 3-part names, separated by underscore:

* The first part of the name is the format of the game state
* The next part of the name is the format of the value matrix
* The third part is either AVX or noAVX, depending on whether AVX2 is required

More parts of the name may be added, to specify different versions of the same algorithm (For example `noForLoops` if this file has manually unrolled all for-loops) below is a short summary of all methods

Vector based methods
------------
These methods store the state as a 32 entry vector, of how many pieces are at each location.

In the default format, entry 0 in the vector is player 0's number of pieces at position 0 (i.e. not started yet), entry 1 to 14 are how many pieces player 0 has on tile 1 to 14, and entry 15 is how many pieces player 0 has finished. The next 16 entries tell the same for player 1.

Calculating the value is basically equivalent to calculating $V^T M V$, where $V$ is the state vector, and $M$ is the value matrix. All files starting with `vector8bit_denseFull8bit` (Or 16 bit) perform this multiplication in various ways: Some use two for-loops, some use AVX intrinsics such as `_m265_madd_epi16` to accelerate this multiplication with SIMD, and some are further accelerated by manual unrolling of for-loops.

In one case, I used C++ templates to automatically unroll the for-loops, but that proved to have significantly worse performance than manually unrolling.


The default format is very logical to use, and easy to read, but it is a little awkward that entry 0,15,16 and 31 can be between 0 and 7, and all other entries can only be 0, 1 (there can only be 0 or 1 pieces on each tile at the same time).

In the alternative vector format *backformat* the number of pieces player 0 has at tile 1 through 14 goes first, then player 1's number of pieces at 1 through 14, and finally player 0's unstarted, player 0's finished, player 1's unstarted and player 1's finished pieces.

In that case we know that the multiplications for all entries between 0 and 28 are with 0 or 1, which means we can replace them with an AVX mask instruction (which is much faster than multiplications).

The algorithm using this format: `vector16bit_dense3quarter16bit_AVX_mask` (and the for-loop free version of the same thing) is the fastest vector based version by far

The matrix does need to be written in this entirely new new basis, hence why there is a unique matrix class for this version, this matrix class is also a little smaller (because it leaves out the 1 quarter of the matrix which is guaranteed to be 0).


Full performance report
----------------------
Actual computation time, and the relative order of the different implementation may vary from system to system.


TBD, when all algorithms exist, including index based