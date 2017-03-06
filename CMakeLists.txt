cmake_minimum_required(VERSION 3.6)
project(NP_HA_FTP)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/client.cpp)
add_executable(NP_HA_FTP ${SOURCE_FILES})
