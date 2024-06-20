set(SOURCES Player.cpp)

add_library(Entities ${SOURCES})
target_include_directories(Entities PUBLIC ${CMAKE_SOURCE_DIR}/inc)
