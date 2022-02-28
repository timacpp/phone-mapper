cmake_minimum_required(VERSION 3.20)
project(phone_mapper)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE src/maptel.cc src/maptel.h)
add_executable(test_c test/maptel_test1.c ${SOURCE})
add_executable(test_cpp test/maptel_test2.cc ${SOURCE})
