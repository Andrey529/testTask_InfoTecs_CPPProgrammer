cmake_minimum_required(VERSION 3.24)
project(Program2)

set(CMAKE_CXX_STANDARD 20)

include_directories(../Logger/include)
include_directories(../libs/spdlog/include)

ADD_LIBRARY(Logger STATIC ../Logger/src/Loggable.cpp ../Logger/src/Logger.cpp)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp
        src/Program2/Program2.cpp src/Program2/Program2.h
        src/NetworkConnecter/NetworkConnecter.cpp src/NetworkConnecter/NetworkConnecter.h
        src/DataProcessor/DataProcessor.cpp src/DataProcessor/DataProcessor.h)
target_link_libraries(${CMAKE_PROJECT_NAME} Logger)