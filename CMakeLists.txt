cmake_minimum_required(VERSION 3.10)
project(technical_test_linx)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_DIRECTORY "src")

include_directories("deps/json")

add_executable(processador ${SOURCE_DIRECTORY}/main.cpp src/Product.h src/Tokenizer.h src/Tokenizer.cpp)
# target_include_directories(processador PRIVATE ./deps/json)