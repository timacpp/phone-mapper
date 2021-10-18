cmake_minimum_required(VERSION 3.20)
project(phone_mapper)

set(CMAKE_CXX_STANDARD 14)

add_executable(phone_mapper main.cpp maptel.cc maptel.h main.cpp)
