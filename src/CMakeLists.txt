
add_library(testStates
        ../include/testStates.h testStates.cpp)


#Generate targets for every possible implementation of getValue
file(GLOB getValueAlgorithms "getValue/*.cpp")
foreach (valueAlgorithm_file ${getValueAlgorithms})
    add_compile_definitions(REPEATS=1000000)
    add_compile_definitions(ALGORITHM_NAME=${valueAlgorithm})
    get_filename_component(valueAlgorithm ${valueAlgorithm_file} NAME_WE)
    add_executable(getValue_${valueAlgorithm}_speedtest)
    target_sources(getValue_${valueAlgorithm}_speedtest PRIVATE getValue_speedTest.cpp ${valueAlgorithm_file})
    target_link_libraries(getValue_${valueAlgorithm}_speedtest PRIVATE testStates)
endforeach ()

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE getValue_speedTest.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE testStates)
target_link_libraries(${PROJECT_NAME} PRIVATE getValueNoAvxStateIndices)
