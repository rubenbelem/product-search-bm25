cmake_minimum_required(VERSION 3.10)
project(spelling_corrector)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(".")

FILE(GLOB SOURCES_AND_HEADERS "./*.cpp" "./*.hpp")

add_library(spelling_corrector_lib ${SOURCES_AND_HEADERS})