cmake_minimum_required(VERSION 3.16) 
project(arduino-serial-comms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(arduino-serial-comms
    src/main.cpp
    src/SerialManager.cpp
    src/SerialDevice.cpp
    src/messageParser.cpp
)

target_include_directories(arduino-serial-comms PRIVATE
    src
)

find_package(log4cxx REQUIRED)
find_package(GTest REQUIRED)

target_link_libraries(arduino-serial-comms PRIVATE log4cxx)

add_executable(arduino-serial-comms-tests
    test/main.cpp
    test/SerialManagerTest.cpp
    src/SerialManager.cpp
    src/SerialDevice.cpp
    src/TSerialDevice.cpp
    src/messageParser.cpp
)

target_include_directories(arduino-serial-comms-tests PRIVATE src)
target_link_libraries(arduino-serial-comms-tests PRIVATE GTest::GTest log4cxx)