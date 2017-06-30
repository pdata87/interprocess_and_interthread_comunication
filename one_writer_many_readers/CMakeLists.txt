cmake_minimum_required(VERSION 3.7)
project(one_writer_many_readers)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c List.c List.h)

add_executable(one_writer_many_readers ${SOURCE_FILES})
TARGET_LINK_LIBRARIES( one_writer_many_readers
        pthread
        )