#include "linked_list.h"
#include "test_common.h"

START_TEST (simple_test) {
  linked_list *test = linked_list_create();
  int test_int = 1;
  int check = linked_list_append(test, (void *) test_int);
  ck_assert_int_eq(check, 0);
  void *ret;
  check = linked_list_dequeue(test, &ret);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(test_int, (ssize_t)ret);
  linked_list_destroy(test);
}
END_TEST

START_TEST (dequeue_test) {
  linked_list *test = linked_list_create();
  void *ret;
  int check = linked_list_dequeue(test, &ret);
  ck_assert_int_ne(check, 0);
  linked_list_destroy(test);
}
END_TEST

START_SUITE(linked_list_suite) {
  Suite *s = suite_create("Linked List");
  TCase *tc_core = tcase_create("Simple Test");

  tcase_add_test(tc_core, simple_test);
  suite_add_tcase(s, tc_core);

  return s;
}
