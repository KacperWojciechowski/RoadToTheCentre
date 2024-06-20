set(SOURCES Galaxy.cpp
            Planet.cpp
            SolarSystem.cpp)

add_library(GameMap ${SOURCES})
target_include_directories(GameMap PUBLIC ${CMAKE_SOURCE_DIR}/inc)