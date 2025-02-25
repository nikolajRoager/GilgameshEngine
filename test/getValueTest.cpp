/// Test the accuracy of the algorithm supplied

#include <iostream>
#include <chrono>
#include "getValue.h"
#include "testStates.h"

#ifndef ALGORITHM_NAME
#warning "Please set name in CMake using add_compile_definitions"
#define ALGORITHM_NAME unnamed
#endif
#ifndef REPEATS
#define REPEATS 1000000
#elif REPEATS<1
#warning "Number of Repeats is illegal, using 1000000"
#define REPEATS 1000000
#endif

//Converts a macro to a string
#define STRING(x) #x
#define TO_STRING(x) STRING(x)

 int main(int argc, char* argv[]) {
    std::cout << "test on algorithm '" <<TO_STRING(ALGORITHM_NAME)<<"'\n";

    auto examples =testStates();
    auto start = std::chrono::high_resolution_clock::now();


    //We will keep looping through all examples until we have enough repeats (we can safely assume REPEATS>>examples)
    for (int i = 0; i < REPEATS;)
        for (auto & example : examples) {
            //Volatile hopefully prevents the compiler from optimizing away my speed test (if the execution time literally drops to 0, it has done so anyway)
                //I don't care about the result, this is a speed test, not accuracy test
                volatile int16_t result = getValue(example.state,example.matrix);
                ++i;
                if (i>REPEATS)
                    break;
        }
    auto stop= std::chrono::high_resolution_clock::now();
    auto duration = stop-start;
    std::cout<<"Took on average "<<(duration_cast<std::chrono::nanoseconds>(duration)/(REPEATS)).count()<<" ns";
    return 0;
}
