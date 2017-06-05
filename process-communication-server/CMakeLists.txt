cmake_minimum_required(VERSION 3.7)
project(process_communication-server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SocketServer.cpp SocketServer.h Client.cpp Client.h Message.cpp Message.h ConnectionPoll.cpp ConnectionPoll.h)
add_executable(process_communication ${SOURCE_FILES})