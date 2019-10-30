cmake_minimum_required(VERSION 3.10)
project(technical_test_linx)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_DIRECTORY "src")

add_subdirectory("deps/nuspell")
include_directories("deps/json")
include_directories("deps/nuspell/src/nuspell")
include_directories("deps/nuspell/src/hunspell")
include_directories("deps/nuspell/src/parsers")

FILE(GLOB SOURCES_AND_HEADERS "${SOURCE_DIRECTORY}/*.cpp" "${SOURCE_DIRECTORY}/*.h")
add_executable(processor ${SOURCE_DIRECTORY}/main.cpp  ${SOURCES_AND_HEADERS})
target_link_libraries(processor nuspell)
