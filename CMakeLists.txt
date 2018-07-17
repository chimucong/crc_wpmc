cmake_minimum_required(VERSION 3.10)
project(crc_wpmc)

set(CMAKE_CXX_STANDARD 11)

add_executable(crc_wpmc main.cpp CrcBase.cpp Crc8Base.cpp Crc8Base.h Crc16Base.cpp Crc16Base.h Crc16CCITT.cpp Crc16CCITT.h Crc32Base.cpp Crc32Base.h Crc32.cpp Crc32.h Crc64Base.cpp Crc64Base.h Crc64ISO.cpp Crc64ISO.h)