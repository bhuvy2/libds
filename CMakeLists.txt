cmake_minimum_required(VERSION 2.8)
include(GNUInstallDirs)
set(LIBRARY_OUTPUT_PATH "libs")
set(EXECUTABLE_OUTPUT_PATH "bin")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set (CMAKE_C_STANDARD 11)
# Project's name
option(CODE_COVERAGE "Build test programs" OFF)

IF(CODE_COVERAGE)
  include(CodeCoverage)
  APPEND_COVERAGE_COMPILER_FLAGS()
ENDIF(CODE_COVERAGE)

add_subdirectory(src)
enable_testing()
add_subdirectory(test)
