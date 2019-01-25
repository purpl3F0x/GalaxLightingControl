cmake_minimum_required(VERSION 3.13)
project(GalaxLightingControl)

set(CMAKE_CXX_STANDARD 11)


add_executable(GalaxLightingControl main.cpp GalaxLighting.cpp color.hpp)
