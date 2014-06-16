cmake_minimum_required(VERSION 2.8)
project(m3meka)

# Options

# Compile in c++11 (not compiling yet)
OPTION(USE_C++11 "Use c++11 (not compiling yet 10 avril 2014)" 0)


if(USE_C++11)
	set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")
	message("-- Using c++11")
endif(USE_C++11)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")



add_subdirectory(src/m3)
add_subdirectory(python)

