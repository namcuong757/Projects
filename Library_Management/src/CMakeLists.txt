cmake_minimum_required(VERSION 3.12)
project(library VERSION 1.0.0 LANGUAGES CXX)

add_library(
	tool-help
	adding.h
	adding.cpp
	checkOutnIn.h
	checkOutnIn.cpp
	data.h
	data.cpp
	library.h
	library.cpp
	menu.h
	menu.cpp
)
add_executable(library main.cpp)

target_link_libraries(library tool-help)

