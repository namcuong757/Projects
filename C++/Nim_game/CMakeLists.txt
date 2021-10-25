cmake_minimum_required(VERSION 3.12)
project(nim-game VERSION 1.0.0 LANGUAGES CXX)

add_library(
	tool-help
	option.h
	option.cpp
)
add_executable(nim-game main.cpp)

target_link_libraries(nim-game tool-help)
