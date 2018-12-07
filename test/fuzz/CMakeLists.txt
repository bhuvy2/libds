
set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
include_directories(.)

add_executable(fuzz_queue_test_libds
	fuzz_queue.c
	)
target_link_libraries(fuzz_queue_test_libds ds check m rt pthread subunit gcov)

add_executable(fuzz_stack_test_libds
	fuzz_stack.c
	)
target_link_libraries(fuzz_stack_test_libds ds check m rt pthread subunit gcov)
