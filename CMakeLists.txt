cmake_minimum_required(VERSION 3.10)
project(technical_test_linx)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_DIRECTORY "src")

include_directories("deps/json")
include_directories("deps/spellingcorrector")
add_subdirectory("deps/spellingcorrector")

FILE(GLOB SOURCES_AND_HEADERS "${SOURCE_DIRECTORY}/*.cpp" "${SOURCE_DIRECTORY}/*.hpp")
add_executable(processador ${SOURCE_DIRECTORY}/main.cpp  ${SOURCES_AND_HEADERS})
target_link_libraries(processador spelling_corrector_lib -lreadline -lhistory)