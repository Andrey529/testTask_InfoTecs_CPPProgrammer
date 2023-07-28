cmake_minimum_required(VERSION 3.24)
project(Program2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Program2 src/main.cpp
        src/Program2/Program2.cpp src/Program2/Program2.h
        src/NetworkConnecter/NetworkConnecter.cpp src/NetworkConnecter/NetworkConnecter.h
        src/DataProcessor/DataProcessor.cpp src/DataProcessor/DataProcessor.h)
