set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

cmake_minimum_required(VERSION 3.10)

project(1D_transport_equation) #project name

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART True)

set(Config src/Config) #Config dir
set(Zone src/Zone) #Zone class dir
set(SOURCE_EXE src/main.cpp ${Zone}/Zone.cpp ${Zone}/Zone.h ${Config}/Config.h) #src list for exe
add_executable(1D_transport_equation ${SOURCE_EXE})
target_link_libraries(1D_transport_equation -fopenmp)

