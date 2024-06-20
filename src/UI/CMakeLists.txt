set (SOURCES TextInterface.cpp)

add_library(UI ${SOURCES})
target_include_directories(UI PUBLIC ${CMAKE_SOURCE_DIR}/inc)