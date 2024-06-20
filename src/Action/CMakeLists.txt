set (SOURCES ActionValidator.cpp
             GeneralAction.cpp)

add_library(Action ${SOURCES})
target_include_directories(Action PUBLIC ${CMAKE_SOURCE_DIR})