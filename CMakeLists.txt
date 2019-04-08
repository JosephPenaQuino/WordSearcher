cmake_minimum_required(VERSION 3.12)
project(CLion C)

set(CMAKE_C_STANDARD 11)

add_executable(CLion main.c)
add_executable(TestReading test_reading.c)
add_executable(Indhira indhira.c)