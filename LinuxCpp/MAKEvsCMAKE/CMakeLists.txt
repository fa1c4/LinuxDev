# cmake -DCMAKE_BUILD_TYPE=Release .
# cmake --build .

# CMakeLists for singleRead
# cmake_minimum_required(VERSION 3.10)
# project(singleRead)
# notice that there is no ',' in the add_executable()
# add_executable(singleRead singleRead.cpp)

# CMakeLists for ParallRead
cmake_minimum_required(VERSION 3.10)
project(ParallRead)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lpthread -std=c++11")
add_executable(ParallRead ParallRead.cpp)
target_link_libraries(ParallRead pthread)
