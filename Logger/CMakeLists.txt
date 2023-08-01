cmake_minimum_required(VERSION 3.24)
project(Logger)

set(CMAKE_CXX_STANDARD 20)
include_directories(../libs/spdlog/include)

add_library(Logger STATIC
        src/Logger.cpp src/Logger.h
        src/Loggable.cpp src/Loggable.h)
