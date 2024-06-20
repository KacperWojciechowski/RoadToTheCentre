set (SOURCES TravelAgent.cpp)

add_library(Mechanics ${SOURCES})
target_include_directories(Mechanics PUBLIC ${CMAKE_SOURCE_DIR})
