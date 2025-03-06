project(MyLibTests LANGUAGES CXX)

#add_executable(MyLibTests src/MyLibTests.cpp)

#target_link_libraries(MyLibTests PRIVATE MyLib)

# Custom target that ensures all programs are built
add_custom_target(BuildSpeedtest)

add_compile_definitions(REPEATS=1000000)
#Generate targets for every possible implementation of getValue
file(GLOB getValueAlgorithms "../src/getValue/*.cpp")
list(REMOVE_ITEM getValueAlgorithms "*constant.cpp")
foreach (valueAlgorithm_file ${getValueAlgorithms})
    get_filename_component(valueAlgorithm ${valueAlgorithm_file} NAME_WE)
    add_executable(getValue_${valueAlgorithm}_speedtest)
    target_sources(getValue_${valueAlgorithm}_speedtest PRIVATE getValue_speedTest.cpp ${valueAlgorithm_file})
    target_link_libraries(getValue_${valueAlgorithm}_speedtest PRIVATE testStates)

    add_dependencies(BuildSpeedtest getValue_${valueAlgorithm}_speedtest)
    add_test(NAME getValue_${valueAlgorithm}_speedtest COMMAND getValue_${valueAlgorithm}_speedtest)
endforeach ()

add_executable(
        MatrixTests
        MatrixTests.cpp
)
target_link_libraries(
        MatrixTests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MatrixTests)