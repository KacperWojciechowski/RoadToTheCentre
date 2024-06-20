cmake_minimum_required(VERSION 3.10)
project(RoadToTheCentre)

set(CMAKE_CXX_STANDARD 20)

include_directories(inc)

add_subdirectory(src)

add_executable(Game Main.cpp)
target_link_libraries(Game PRIVATE 
                           Core
                           Entities
                           GameMap
                           Mechanics
                           Services
                           UI
                           Utility
                           Action)