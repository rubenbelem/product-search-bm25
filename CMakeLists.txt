cmake_minimum_required(VERSION 3.10)
project(product_search_bm25)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_DIRECTORY "src")

include_directories("deps/json")
include_directories("deps/spellingcorrector")
add_subdirectory("deps/spellingcorrector")

FILE(GLOB SOURCES_AND_HEADERS "${SOURCE_DIRECTORY}/*.cpp" "${SOURCE_DIRECTORY}/*.hpp")
add_executable(processor ${SOURCE_DIRECTORY}/main.cpp  ${SOURCES_AND_HEADERS})
target_link_libraries(processor spelling_corrector_lib -lreadline -lhistory)
