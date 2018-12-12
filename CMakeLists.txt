cmake_minimum_required(VERSION 2.8)
include(GNUInstallDirs)
set(LIBRARY_OUTPUT_PATH "libs")
set(EXECUTABLE_OUTPUT_PATH "bin")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
# Project's name
add_subdirectory(src)
enable_testing()
add_subdirectory(test)
