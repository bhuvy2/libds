add_executable(unit_test_libds
  test_main.c
  linked_list_test.c
  vector_test.c)

set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
include_directories(.)
target_link_libraries(unit_test_libds ds check m rt pthread subunit gcov)

add_test(NAME unit
  COMMAND unit_test_libds)

IF(CODE_COVERAGE)
  set(COVERAGE_LCOV_EXCLUDES 'test/*')
SETUP_TARGET_FOR_COVERAGE_LCOV(NAME unit_test_cov
  EXECUTABLE unit_test_libds
  DEPENDENCIES unit_test_libds ds)
ENDIF(CODE_COVERAGE)
