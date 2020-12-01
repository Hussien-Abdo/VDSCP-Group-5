project(VDSProject_test CXX C)
cmake_minimum_required(VERSION 2.6.2)


add_executable(VDSProject_test main_test.cpp)
target_link_libraries(VDSProject_test Manager)
target_link_libraries(VDSProject_test gtest gtest_main pthread)

# 'Google_test' is the subproject name
project(test)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'tests' is source file with tests
add_executable(Google_Tests_run tests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)