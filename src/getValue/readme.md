Get value Algorithms
-------------------

This folder contains different implementations of the getValue function, defined in `include/getValue.h`
'

All files in this folder are automatically compiled, and included in the speed test

The file constant.cpp literally just returns 0, it is only used as a baseline for the speed test.

The names of all the other files indicate the formats, extension, and algorithms used; they are written in camelCase with 3-part names, separated by underscore:

* The first part of the name is the format of the game state
* The next part of the name is the format of the value matrix
* The final part is either AVX or noAVX, depending on whether AVX2 is required

Additionally a fourth part of the name can be added, if there are some special properties of this algorithm (for example `noForLoop`, if all for-loops have been manually unrolled)