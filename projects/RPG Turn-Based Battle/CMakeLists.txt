cmake_minimum_required(VERSION 3.13)
project(RPG-Game)

# Use C++20 (Change to 17 if needed)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files in src/ excluding main.cpp
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")
list(REMOVE_ITEM SRC_FILES "${SRC_DIR}/main.cpp")

# Add the executable
add_executable(rpg_game ${SRC_FILES} "${SRC_DIR}/main.cpp")
target_include_directories(rpg_game PRIVATE ${SRC_DIR})
