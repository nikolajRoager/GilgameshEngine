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

    std::vector<std::pair<void*,void*>> example_pointers;
    for (auto var : examples) {
        //Convert to whatever format this implementation uses
        void * state_ptr = loadStateWorkspace(var.state);
        void * matrix_ptr= loadMatrixWorkspace(var.matrix);
        example_pointers.push_back(std::make_pair(state_ptr,matrix_ptr));
    }

    std::vector<int> results(examples.size());

    auto start = std::chrono::high_resolution_clock::now();
    //We will keep looping through all examples until we have enough repeats (we can safely assume REPEATS>>examples)
    for (int i = 0; i < cycles ;++i)
        for (int j = 0; j < examples.size();++j) {
            //Volatile hopefully prevents the compiler from optimizing away my speed test (if the execution time literally drops to 0, it has done so anyway)
            volatile int res = getValue(example_pointers[j].first, example_pointers[j].second);
            results[j] = res;
        }
    //Stop the timer, and print the result
    auto stop= std::chrono::high_resolution_clock::now();
    auto duration = stop-start;

    std::cout<<"Took on average "<<(duration_cast<std::chrono::nanoseconds>(duration)/(cycles*examples.size())).count()<<" ns"<<std::endl;

    //Now, we donøt need these any more
    for (auto pair : example_pointers) {
        freeWorkspace(pair.first,pair.second);
    }

    //Kindly also verify that the result is correct (if the result is not correct, the speed-test is meaningless, unless this was some kind of benchmark where the result doesnn't matter
    if (ignoreOutput()) {
        std::cout<<"Benchmark! (the result is wrong, but that is ok)"<<std::endl;
        return 0;
    }
    for (int i = 0; i < examples.size(); ++i) {
        if (examples[i].value!=results[i]) {
            std::cout<<"Fails test "<<i<<" got "<<results[i]<<" expected "<<examples[i].value<<std::endl;
            return 1;
        }
    }
    std::cout<<"all test cases succeeded!"<<std::endl;
    return 0;
}
