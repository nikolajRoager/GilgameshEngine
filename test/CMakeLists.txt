project(MyLibTests LANGUAGES CXX)

#add_executable(MyLibTests src/MyLibTests.cpp)

#target_link_libraries(MyLibTests PRIVATE MyLib)


#Generate test targets for every possible implementation of getValue
file(GLOB getValueAlgorithms "../src/getValue/*.cpp")
list(REMOVE_ITEM getValueAlgorithms "../src/getValue/constant.cpp")


foreach (valueAlgorithm_file ${getValueAlgorithms})

    get_filename_component(valueAlgorithm ${valueAlgorithm_file} NAME_WE)
        add_compile_definitions(ALGORITHM_NAME=${valueAlgorithm})
        add_executable(getValue_${valueAlgorithm}_test)
        target_sources(getValue_${valueAlgorithm}_test PRIVATE getValueTest.cpp ${valueAlgorithm_file})
        target_link_libraries(getValue_${valueAlgorithm}_test PRIVATE testStates)

        add_test(NAME ${valueAlgorithm} COMMAND getValue_${valueAlgorithm}_test)
endforeach ()