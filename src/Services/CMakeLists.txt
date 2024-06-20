set(SOURCES GameTimeService.cpp)

add_library(Services ${SOURCES})
target_include_directories(Services PUBLIC ${CMAKE_SOURCE_DIR})