cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 14)

project("Game")
add_executable(${PROJECT_NAME} "src/main.cpp")