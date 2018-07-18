cmake_minimum_required(VERSION 3.10)
project(crc_wpmc)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-O3")

add_executable(crc_wpmc main.cpp
        CrcBase.cpp CrcBase.h
        Crc8Base.cpp Crc8Base.h
        Crc16Base.cpp Crc16Base.h
        Crc16CCITT.cpp Crc16CCITT.h
        Crc32Base.cpp Crc32Base.h
        Crc32.cpp Crc32.h
        Crc64Base.cpp Crc64Base.h
        Crc64ISO.cpp Crc64ISO.h Crc8CCITT.cpp Crc8CCITT.h Crc8.cpp Crc8.h Crc8WCDMA.cpp Crc8WCDMA.h Crc16DECT.cpp Crc16DECT.h Crc16CDMA2000.cpp Crc16CDMA2000.h Crc32Q.cpp Crc32Q.h Crc32C.cpp Crc32C.h)