cmake_minimum_required(VERSION 3.11)

project(bit_twiddling_hacks
        VERSION 0.1.0
        LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_executable(bit_twiddling_hacks source/bit_twiddling_hacks.h source/bit_twiddling_hacks.c)