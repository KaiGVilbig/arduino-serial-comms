cmake_minimum_required(VERSION 3.16) 
project(arduino-serial-comms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(arduino-serial-comms
    src/main.cpp
    src/SerialManager.cpp
    src/SerialDevice.cpp
)

target_include_directories(arduino-serial-comms PRIVATE
    src
)

find_package(log4cxx REQUIRED)
target_link_libraries(arduino-serial-comms PRIVATE log4cxx)