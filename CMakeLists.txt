cmake_minimum_required(VERSION 3.20)
project(CM2)

set(CMAKE_CXX_STANDARD 20)

add_library(CM2_obj state_machine.hpp
        state_machine.cpp parser.hpp
)
add_executable(CM2_sm main_sm.cpp)
add_executable(CM2_parser main_parser.cpp)
add_executable(CM2_tests tests.cpp)

find_package(Catch2 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
target_include_directories(CM2_tests PRIVATE src)
target_link_libraries(CM2_tests PRIVATE CM2_obj GTest::gtest_main)
target_include_directories(CM2_sm PRIVATE src)
target_include_directories(CM2_parser PRIVATE src)
target_link_libraries(CM2_sm PRIVATE CM2_obj)
target_link_libraries(CM2_parser PRIVATE CM2_obj)