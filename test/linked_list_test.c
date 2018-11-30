#include "linked_list.h"
#include <check.h>
#include <stdio.h>

START_TEST (simple_test) {
  linked_list *test = linked_list_create();
  int test_int = 1;
  linked_list_append(test, (void *) test_int);
  int ret = (int)linked_list_dequeue(test);
  ck_assert_int_eq(test_int, ret);
}
END_TEST

Suite *linked_list_suite(void){
  Suite *s;
  TCase *tc_core;
  s = suite_create("Linked List");
  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, simple_test);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = linked_list_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed != 0);
}
