cmake_minimum_required(VERSION 3.20)
project(LongArith)
set(CMAKE_CXX_STANDARD 20)
add_executable(LongArith main.cpp BigInt.cpp fft.cpp test.cpp)
