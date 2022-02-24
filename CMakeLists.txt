cmake_minimum_required(VERSION 3.21)
project(raycaster)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAME_CXX_FLAGS} -Wall -std=c++20")

find_package(fmt)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(raycaster src/raycaster.cpp)
target_link_libraries(raycaster ${SDL2_LIBRARIES} fmt::fmt)
