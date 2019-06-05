#pragma once
#include <check.h>

/**
 * The return type of all testing functions
 */
typedef Suite *(*test_func_type)(void);


/**
 * Creates aligned tests and descriptions
 * They must be aligned or you will get a SIGILL
 * because we iterate over them through sections
 */
typedef struct {
	test_func_type func __attribute__ ((aligned (8)));
} UnitTest;

#define make_unit_test(name) 

/**
 * In the case of multilevel suites, one should probably reorder the section attribute
 *		https://stackoverflow.com/questions/24283277/merging-global-arrays-at-link-time-filling-a-global-array-from-multiple-compil
 */
#define _PASTE(a, b)    a ## b
#define PASTE(a, b)     _PASTE(a, b)
#define START_SUITE(suite_name) \
		Suite *suite_name(void); \
    volatile const UnitTest PASTE(__ ## suite_name ## _test_m, __LINE__) __attribute__((section("tests_"))) __attribute__ ((used)) = ((UnitTest){.func = (test_func_type)suite_name});       \
    Suite *suite_name(void)

typedef struct {
  const char *desc;
  void *test;
  int timeout;
} test_desc;
