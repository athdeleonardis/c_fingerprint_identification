cmake_minimum_required(VERSION 3.16)
project(c_fingerprint_identification LANGUAGES C)

set(CMAKE_CXX_FLAGS "--std=c99")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/test/image")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/test/bit_image")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/test/thinning_zhang_suen")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/test/fingerprint_minutae")

add_subdirectory(src)
add_subdirectory(test)