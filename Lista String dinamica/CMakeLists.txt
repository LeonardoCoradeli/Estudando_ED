cmake_minimum_required(VERSION 3.24)
project(String_dinamica C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(String_dinamica
        main.c
        String_dinamica.c
        String_dinamica.h)
