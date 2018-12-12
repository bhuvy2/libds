#include "vector.h"
#include "test_common.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

START_TEST (test_simple) {
  vector *vec = vector_create();
  ssize_t test_int = 20;
  vector_resize(vec, 2);
  int success = vector_set(vec, 0, (void*)test_int);
  ck_assert_int_eq(success, 0);
  ssize_t ret;
  success = (ssize_t)vector_get(vec, 0, (void **)&ret);
  ck_assert_int_eq(success, 0);
  ck_assert_int_eq(test_int, ret);
  vector_destroy(vec);
  free(vec);
}
END_TEST

START_TEST(test_vector_create){
    vector *vec = vector_create();
    ck_assert(vector_size(vec) == 0);
    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_resize_larger_no_capacity){
    void *get_ret;
    vector *vec = vector_create();
    vector_resize(vec, 2);

    vector_append(vec, strdup("Stuff"));
    ck_assert(vector_size(vec) == 3);
    int append_ret = vector_get(vec, 2, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Stuff");

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_resize_larger_capacity){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    vector_resize(vec, 20);
    vector_set(vec, 0, strdup("Stuff"));

    ck_assert(vector_size(vec) == 20);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Stuff");
    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_resize_smaller){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();
    vector_set(vec, 0, strdup("Stuff"));
    vector_set(vec, 0, strdup("Moar"));
    vector_resize(vec, 1);

    ck_assert(vector_size(vec) == 1);

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_resize_smaller_container){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();
    vector_set(vec, 0, strdup("stuff"));
    vector_resize(vec, 5);

    ck_assert(vector_size(vec) == 5);

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_set){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_ne(append_ret, 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_ne(append_ret, 0);

    vector_append(vec, "Implode");
    vector_append(vec, "Ubuntu");

    ck_assert(vector_size(vec) == 2);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Implode");
    append_ret = vector_get(vec, 1, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Ubuntu");

    vector_destroy(vec);
    free(vec);

}
END_TEST

START_TEST(test_vector_get){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_ne(append_ret, 0);

    append_ret = vector_get(vec, 1, &get_ret);
    ck_assert_int_ne(append_ret, 0);

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_insert_inside){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    //TODO: Write a better test

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST( test_vector_insert_outside){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();
    //TODO: Write a better test
    vector_destroy(vec);
    free(vec);
}
END_TEST


START_TEST(test_vector_delete){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    vector_append(vec, "Ubuntu");
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Ubuntu");

    vector_append(vec, "Elementary");
    append_ret = vector_get(vec, 1, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Elementary");
    vector_delete(vec, 0, NULL);

    ck_assert(vector_size(vec) == 1);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Elementary");

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_append){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    vector_append(vec, "Do you hear the people");
    vector_append(vec, "Sing, singing the song of angry");
    vector_append(vec, "Men, it is the music of a people who");
    vector_append(vec, "Will not be slaves again");
    vector_append(vec, NULL);
    vector_append(vec, "Hello");
    vector_append(vec, "a");
    vector_append(vec, "b");
    vector_append(vec, "c");
    vector_append(vec, "d");

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Do you hear the people");
    append_ret = vector_get(vec, 1, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Sing, singing the song of angry");
    append_ret = vector_get(vec, 2, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert_str_eq(get_ret, "Men, it is the music of a people who");
    append_ret = vector_get(vec, 3, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Will not be slaves again");
    append_ret = vector_get(vec, 4, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    append_ret = vector_get(vec, 5, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Hello");
    append_ret = vector_get(vec, 6, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "a");
    append_ret = vector_get(vec, 7, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "b");
    append_ret = vector_get(vec, 8, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "c");
    append_ret = vector_get(vec, 9, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "d");

    vector_append(vec, "e");

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Do you hear the people");
    append_ret = vector_get(vec, 1, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Sing, singing the song of angry");
    append_ret = vector_get(vec, 2, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert_str_eq(get_ret, "Men, it is the music of a people who");
    append_ret = vector_get(vec, 3, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Will not be slaves again");
    append_ret = vector_get(vec, 4, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    append_ret = vector_get(vec, 5, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "Hello");
    append_ret = vector_get(vec, 6, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "a");
    append_ret = vector_get(vec, 7, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "b");
    append_ret = vector_get(vec, 8, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "c");
    append_ret = vector_get(vec, 9, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "d");

    append_ret = vector_get(vec, 10, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "e");
    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_append_100){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    size_t i = 0;
    for(; i < 100; ++i){
      vector_append(vec,(void *)i);
    }
    ck_assert(vector_size(vec) == 100);

    int conglomeration = 1;
    for(i = 0; i < 100; ++i){
        void* str;
        int append = vector_get(vec, i, &str);
        ck_assert_int_eq(append, 0);
        ck_assert_int_eq((ssize_t)str, i);
    }

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_append_1mil){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    const ssize_t iters = 100000;
    size_t i = 0;
    for(; i < iters; ++i){
      //printf("%lu\n", i);
      vector_append(vec, (void*)i);
    }
    for(i = 0; i < iters; ++i){
        void* str;
        int append = vector_get(vec, i, &str);
        ck_assert_int_eq(append, 0);
        ck_assert_int_eq(i, (ssize_t)str);
    }
    ck_assert(vector_size(vec) == iters);

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_append_empty){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    vector_append(vec, "");

    ck_assert(vector_size(vec) == 1);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert_str_eq(get_ret, "");

    vector_destroy(vec);
    free(vec);
}
END_TEST

typedef struct {
  const char *desc;
  void *test;
  int timeout;
} test_desc;

static test_desc tests[] = {
(test_desc){"test_vector_create", test_vector_create,0,},
(test_desc){"test_vector_resize_larger_no_capacity", test_vector_resize_larger_no_capacity,0,},
(test_desc){"test_vector_resize_larger_capacity", test_vector_resize_larger_capacity,0,},
(test_desc){"test_vector_resize_smaller", test_vector_resize_smaller,0,},
(test_desc){"test_vector_resize_smaller_container", test_vector_resize_smaller_container,0,},
(test_desc){"test_vector_set", test_vector_set,0,},
(test_desc){"test_vector_get", test_vector_get,0,},
(test_desc){"test_vector_insert_inside", test_vector_insert_inside,0,},
(test_desc){"test_vector_insert_outside", test_vector_insert_outside,0,},
(test_desc){"test_vector_delete", test_vector_delete,0,},
(test_desc){"test_vector_append", test_vector_append,0,},
(test_desc){"test_vector_append_100", test_vector_append_100,0,},
(test_desc){"test_vector_append_1mil", test_vector_append_1mil,30,},
(test_desc){"test_vector_append_empty", test_vector_append_empty,0,},
(test_desc){"test_simple", test_simple,0,},
};

START_SUITE(vector_suite) {
  void *get_ret;
  int append_ret;
  Suite *s = suite_create("Vector Suite");
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
