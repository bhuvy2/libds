#include "hash_table.h"
#include "test_common.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int int_cmp(void *k, void *v) {
  return k != v;
}

START_TEST (test_simple_ht) {
  hash_table *tbl = ht_create(int_cmp, 0);
  int key = 1;
  int value = 2;
  ht_set(tbl, key, value);
  int v;
  int success = ht_get(tbl, key, &v);
  ck_assert_int_eq(success, 0);
  ck_assert_int_eq(v, value);
  //vector_destroy(vec);
  //free(vec);
}
END_TEST

static test_desc tests[] = {
                            (test_desc){"test_create_ht", test_simple_ht,0,},
};

START_SUITE(hash_table_suite) {
  void *get_ret;
  int append_ret;
  Suite *s = suite_create("Hash Suite");
  for (int i = 0; i < sizeof(tests)/ sizeof(tests[0]); ++i) {
    test_desc *test = tests + i;
    TCase *tc_core = tcase_create(test->desc);
    tcase_add_test(tc_core, test->test);
    if (test->timeout != 0) {
      tcase_set_timeout(tc_core, (double)test->timeout);
    }
    suite_add_tcase(s, tc_core);
  }

  return s;
}
