cmake_minimum_required(VERSION 3.22.1)

project(ChutesAndLadders)

add_subdirectory(src)
add_subdirectory(test)
enable_testing()

add_test(NAME ChutesAndLaddersTest COMMAND Test)
