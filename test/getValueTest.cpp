/// Test the accuracy of the algorithm supplied on all the test states

#include <iostream>
#include "getValue.h"
#include "testStates.h"
#include <string>

#ifndef ALGORITHM_NAME
#warning "Please set name in CMake using add_compile_definitions"
#define ALGORITHM_NAME unnamed
#endif

//Converts a macro to a string
#define STRING(x) #x
#define TO_STRING(x) STRING(x)

 int main(int argc, char* argv[]) {
    std::cout << "Test algorithm algorithm '" <<TO_STRING(ALGORITHM_NAME)<<"'\n";

     //this algorithm should only be used for speed test, skip it in the unit test (CMake really shouldn't built it)
     if (std::string("constant")==TO_STRING(ALGORITHM_NAME))
         return 0;

    auto examples =testStates();

        for (int i = 0; i < examples.size(); ++i) {
            auto & example = examples[i];
            int16_t result = getValue(example.state,example.matrix);
            if (result != example.value)
            {
              std::cerr<<"Test state "<<i<<" failed, expected value "<<example.value<<" got "<<result<< std::endl;
                return 1;
            }
        }
    return 0;
}
