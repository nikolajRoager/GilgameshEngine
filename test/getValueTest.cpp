/// Test the accuracy of the algorithm supplied on all the test states

#include <iostream>
#include "getValue.h"
#include "testStates.h"
#include <string>
#include "AVX_functions.h"
 int main(int argc, char* argv[]) {

     if (getAVXSupport()==0)
     {
         std::cout<<"AVX is not supported"<<std::endl;
         return 1;
     }


    std::cout << "Test algorithm algorithm '" <<algorithmDescription()<<"'\n";

     //this algorithm should only be used for speed test?, skip it in the unit test
     if (ignoreOutput())
         return 0;

    auto examples =testStates();

        for (int i = 0; i < examples.size(); ++i) {
            auto & example = examples[i];
            //Convert to whatever format this implementation uses
            void * state_ptr = loadStateWorkspace(example.state);
            void * matrix_ptr= loadMatrixWorkspace(example.matrix);
            int result = getValue(state_ptr,matrix_ptr);
            freeWorkspace(state_ptr,matrix_ptr);

            if (result != example.value)
            {
                std::cerr<<"Test state "<<i<<" failed, expected value "<<example.value<<" got "<<result<< std::endl;
                return 1;
            }
        }
    return 0;
}
