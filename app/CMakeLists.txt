cmake_minimum_required(VERSION 3.0)
project(TN)
find_package(Threads)
find_package(FLTK REQUIRED)
find_package( OpenCV REQUIRED )

add_executable(TN 
TN.hpp
Resources.hpp 
Sheet.hpp 
model/Connector.hpp
main.cpp
)

target_include_directories(TN PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(TN ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries(TN clog)
target_include_directories(TN PUBLIC ../xlsxio/include)
target_link_libraries(TN xlsxio_read_STATIC)
target_link_libraries(TN xlsxio_write_STATIC)
target_link_libraries(TN ${FLTK_LIBRARIES})
target_link_libraries(TN ${OpenCV_LIBS})
