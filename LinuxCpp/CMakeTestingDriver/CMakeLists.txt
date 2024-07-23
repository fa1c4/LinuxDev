# mkdir build
# cd build
# cmake -DCMAKE_BUILD_TYPE=Release ..
# cmake --build .
# ctest

# CMakeLists for single Read and ParallRead
cmake_minimum_required(VERSION 3.10)
project(ParallRead)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lpthread -std=c++11")
enable_testing()
add_executable(ParallRead ParallRead.cpp)
add_executable(singleRead singleRead.cpp)
target_link_libraries(ParallRead pthread)
add_test(testRead1 singleRead ../example.txt)
add_test(testRead2 ParallRead ../example.txt)
