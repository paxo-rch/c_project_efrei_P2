cmake_minimum_required(VERSION 3.24)
project(2526_TI301_PJT C)

set(CMAKE_C_STANDARD 11)

add_executable(TI_301_PJT
        main.c utils.c hasse.c tarjan.c matrix.c)

add_executable(part1
        main1.c utils.c hasse.c)

add_executable(part2
        main2.c utils.c hasse.c tarjan.c)

add_executable(part3
        main3.c utils.c hasse.c tarjan.c matrix.c)
