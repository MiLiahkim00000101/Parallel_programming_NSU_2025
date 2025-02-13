cmake_minimum_required(VERSION 3.0)

option(FLOAT "If ON then values of array will be float else - double" OFF)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)


if(FLOAT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -DFLOATVALUESIN")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
endif()


add_executable(main main.cpp)


