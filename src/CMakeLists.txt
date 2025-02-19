add_executable(${PROJECT_NAME}
        ../include/stateVector.h
        testStates.cpp
        ../include/testStates.h
        ../include/stateIndices8bit.h
        ../include/valueMatrix8bit_backformat.h
)
add_library(testStates ../include/testStates.h
        ../include/valueMatrix8bit_backformat.h)


target_sources(${PROJECT_NAME} PRIVATE Component_speedTest.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE testStates)