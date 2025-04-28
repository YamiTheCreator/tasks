cmake_minimum_required(VERSION 3.31)
project(http_url)

set(CMAKE_CXX_STANDARD 20)

add_executable(http_url main.cpp
        incude/CUrlParsingError.h
        incude/CHttpUrl.h
        src/CHttpUrl.cpp
        src/CUrlParsingError.cpp)
