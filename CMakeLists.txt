cmake_minimum_required(VERSION 3.27)
project(basic_software_renderer)

set(CMAKE_CXX_STANDARD 17)

add_executable(basic_software_renderer main.cpp
        tgaimage.cpp
        tgaimage.h
        geometry.h
        model.h
        model.cpp)
