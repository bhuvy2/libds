cmake_minimum_required(VERSION 2.8)
include(GNUInstallDirs)
set(LIBRARY_OUTPUT_PATH "libs")
set(EXECUTABLE_OUTPUT_PATH "bin")
# Project's name
add_subdirectory(src)
add_subdirectory(test)
enable_testing()
add_test (NAME MyTest COMMAND Test)
