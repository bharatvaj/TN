cmake_minimum_required(VERSION 3.0)
project(TN)
find_package( Threads )
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})

add_executable(TN TN.hpp TN.cpp)

target_link_libraries(TN ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries(TN clog)
target_link_libraries(TN Project)
target_link_libraries(TN ${FLTK_LIBRARIES})
