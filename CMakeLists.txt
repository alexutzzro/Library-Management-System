cmake_minimum_required(VERSION 3.30)
project(ProiectCarti C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(ProiectCarti main.c)
target_link_libraries(ProiectCarti ${CURSES_LIBRARIES})