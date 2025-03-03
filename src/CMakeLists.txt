
add_library(testStates testStates.cpp)

# Custom target that ensures all programs are built
add_custom_target(BuildSpeedtest)

add_compile_definitions(REPEATS=1000000)
#Generate targets for every possible implementation of getValue
file(GLOB getValueAlgorithms "getValue/*.cpp")
foreach (valueAlgorithm_file ${getValueAlgorithms})
    get_filename_component(valueAlgorithm ${valueAlgorithm_file} NAME_WE)
    add_executable(getValue_${valueAlgorithm}_speedtest)
    target_sources(getValue_${valueAlgorithm}_speedtest PRIVATE getValue_speedTest.cpp ${valueAlgorithm_file})
    target_link_libraries(getValue_${valueAlgorithm}_speedtest PRIVATE testStates)

    add_dependencies(BuildSpeedtest getValue_${valueAlgorithm}_speedtest)
endforeach ()