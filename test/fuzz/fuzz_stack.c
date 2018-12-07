#include <check.h>
#include <stdio.h>
#include <time.h>
#include "stack.h"

const ssize_t iters = 100000;

START_TEST (fuzz_test) {
  stack *q = new_stack();
  ssize_t sum = 0;
  ssize_t supposed_size = 0;
  void *ret = NULL;
  int val;
  for (ssize_t i = 1; i < iters + 1; ++i) {
    int opt = rand() % 3;
    switch (opt) {
    case 0: // size check
      ck_assert_int_eq(supposed_size, stack_size(q));
      break;
    case 1: // pop check
      if (supposed_size == 0) {
        //printf("Invalid pop\n");
        val = stack_pop(q, &ret);
        ck_assert_int_ne(val, 0);
        ret = NULL;
      } else {
        val = stack_pop(q, &ret);
        ck_assert_int_eq(val, 0);
        ck_assert_int_lt((ssize_t)ret, i);
        sum -= (ssize_t)ret;
        ck_assert_int_ge(sum, 0);
        ret = NULL;
        supposed_size--;
      }
      break;
    case 2: // push check
      ret = (void *)i;
      val = stack_push(q, ret);
      ck_assert_int_eq(val, 0);
      sum += i;
      supposed_size++;
      ret = NULL;
      break;
    }
  }

  int prev = iters+2;

  while (stack_pop(q, &ret) == 0) {
    ssize_t comp = (ssize_t)ret;
    ck_assert_int_lt(comp, prev);
    prev = comp;
    sum -= comp;
  }
  ck_assert_int_eq(sum, 0);
}
END_TEST

Suite *stack_fuzz_suite() {
  Suite *s = suite_create("Stack Suite");
  TCase *tc_core = tcase_create("Fuzz Test");

  tcase_add_test(tc_core, fuzz_test);
  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  srand(time(NULL));
  int ret;

  Suite *s = stack_fuzz_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  ret |= number_failed;

  return !!ret;
}
