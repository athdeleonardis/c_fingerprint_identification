cmake_minimum_required(VERSION 3.16)
project(c_fingerprint_identification LANGUAGES C)

set(CMAKE_CXX_FLAGS "--std=c99")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/test/test_image")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/test/test_bit_image")

add_subdirectory(src)
add_subdirectory(test)