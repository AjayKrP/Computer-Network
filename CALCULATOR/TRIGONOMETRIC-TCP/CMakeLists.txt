cmake_minimum_required(VERSION 3.8)
project(TrigCalc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES client.cpp packet.h server.cpp)
add_executable(TrigCalc ${SOURCE_FILES})