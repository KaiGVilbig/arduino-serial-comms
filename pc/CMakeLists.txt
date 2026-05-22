cmake_minimum_required(VERSION 3.16) 
project(arduino-serial-comms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(arduino-serial-comms
    src/main.cpp
    src/SerialDevice.cpp
)

target_include_directories(arduino-serial-comms PRIVATE
    src
)