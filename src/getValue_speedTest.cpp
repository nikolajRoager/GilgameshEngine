 ///
/// Test the speed of the various components of the Royal game of UR, that being:
/// 1 Calculate value given a value matrix and a state, either in the form of a "state vector" or "state indices"
/// 2 Generate all legal next states, given a state vector

#include <iostream>
#include <chrono>
#include "getValue.h"
#include "testStates.h"

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
    std::cout << "Speed test on algorithm '" <<algorithmDescription()<<"'\n";

    auto examples =testStates();
     int cycles = REPEATS/examples.size();
    auto start = std::chrono::high_resolution_clock::now();
    //We will keep looping through all examples until we have enough repeats (we can safely assume REPEATS>>examples)
    for (int i = 0; i < cycles ;++i)
        for (auto & example : examples) {
            //Volatile hopefully prevents the compiler from optimizing away my speed test (if the execution time literally drops to 0, it has done so anyway)
            //I don't care about the result, this is a speed test, not accuracy test
            volatile int result = getValue(&(example.state.data[0]), (example.matrix.data()));
        }
    auto stop= std::chrono::high_resolution_clock::now();
    auto duration = stop-start;
    std::cout<<"Took on average "<<(duration_cast<std::chrono::nanoseconds>(duration)/(cycles*examples.size())).count()<<" ns";
    return 0;
}
