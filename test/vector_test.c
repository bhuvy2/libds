#include "vector.h"
#include "test_common.h"

START_TEST (simple_test) {
  vector *vec = vector_create();
  ssize_t test_int = 20;
  int success = vector_set(vec, 0, (void*)test_int);
  ck_assert_int_eq(success, 0);
  ssize_t ret;
  success = (ssize_t)vector_get(vec, 0, (void **)&ret);
  ck_assert_int_eq(success, 0);
  ck_assert_int_eq(test_int, ret);
}
END_TEST

START_SUITE(vector_suite) {
  Suite *s = suite_create("Vector Suite");
  TCase *tc_core = tcase_create("Simple Test");

  tcase_add_test(tc_core, simple_test);
  suite_add_tcase(s, tc_core);

  return s;
}
