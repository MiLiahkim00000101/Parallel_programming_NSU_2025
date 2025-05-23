cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)



add_executable(main main.cpp)
target_compile_options(main PRIVATE -fopenmp)
