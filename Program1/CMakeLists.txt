cmake_minimum_required(VERSION 3.24)
project(Program1)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(../Logger/include)
include_directories(../libs/spdlog/include)

ADD_LIBRARY(Logger STATIC ../Logger/src/Loggable.cpp ../Logger/src/Logger.cpp)

add_executable(Program1 src/main.cpp
        src/SharedBuffer/SharedBuffer.cpp src/SharedBuffer/SharedBuffer.h
        src/DataProcessor/DataProcessor.cpp src/DataProcessor/DataProcessor.h
        src/Program1/Program1.cpp src/Program1/Program1.h
        src/NetworkConnecter/NetworkConnecter.cpp src/NetworkConnecter/NetworkConnecter.h)
target_link_libraries(${CMAKE_PROJECT_NAME} Logger)
