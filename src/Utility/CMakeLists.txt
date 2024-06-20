set (SOURCES RandomGenerator.cpp)

add_library(Utility ${SOURCES})
target_include_directories(Utility PUBLIC ${CMAKE_SOURCE_DIR})