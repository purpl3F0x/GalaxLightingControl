cmake_minimum_required(VERSION 3.13)
project(GalaxLightingControl)

set(CMAKE_CXX_STANDARD 11)

link_directories(${CMAKE_SOURCE_DIR})

add_executable(GalaxLightingControl main.cpp GalaxLighting.cpp GalaxLighting.hpp color.hpp)
