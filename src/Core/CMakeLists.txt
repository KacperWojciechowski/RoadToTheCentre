set(SOURCES Game.cpp)

add_library(Core ${SOURCES})
target_include_directories(Core PUBLIC ${CMAKE_SOURCE_DIR}/inc)