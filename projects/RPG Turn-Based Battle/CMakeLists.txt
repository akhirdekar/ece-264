cmake_minimum_required(VERSION 3.13)
project(RPG-Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")
list(REMOVE_ITEM SRC_FILES "${SRC_DIR}/main.cpp")

add_executable(rpg_game ${SRC_FILES} "${SRC_DIR}/main.cpp")
target_include_directories(rpg_game PRIVATE ${SRC_DIR})
