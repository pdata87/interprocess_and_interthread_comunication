cmake_minimum_required(VERSION 3.7)
project(process_communication)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SocketServer.cpp SocketServer.h)
add_executable(process_communication ${SOURCE_FILES})