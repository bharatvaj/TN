cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
if(WIN32)
    add_compile_options(-static-libstdc++)
endif()
set (CMAKE_CXX_STANDARD 11)
add_subdirectory(clog ${CMAKE_SOURCE_DIR}/build/clog/)
add_subdirectory(libxlsxwriter ${CMAKE_SOURCE_DIR}/build/libxlsxwriter)
#add_subdirectory(tesseract ${CMAKE_SOURCE_DIR}/build/tesseract)

#main application
add_subdirectory(app ${CMAKE_SOURCE_DIR}/build/app)


