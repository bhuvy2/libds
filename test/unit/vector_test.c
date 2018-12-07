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
    ck_assert(strcmp(get_ret, "Stuff") == 0);

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_resize_larger_capacity){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    vector_set(vec, 0, strdup("Stuff"));
    vector_resize(vec, 20);

    ck_assert(vector_size(vec) == 20);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Stuff") == 0);
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

    ck_assert(vector_size(vec) == 10);

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_set){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Connical");
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Ubuntu");

    vector_set(vec, 0, "Implode");

    ck_assert(vector_size(vec) == 2);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Implode") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Ubuntu") == 0);

    vector_destroy(vec);
    free(vec);

}
END_TEST

START_TEST(test_vector_get){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Connical") ==0);

    append_ret = vector_get(vec, 1, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Ubuntu") ==0);

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST( test_vector_insert_inside){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Connical");
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Ubuntu");
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Ubuntu");

    vector_insert(vec, 0, "Elementary");

    ck_assert(vector_size(vec) == 3);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Elementary") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Connical") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Ubuntu") == 0);


    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST( test_vector_insert_outside){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Connical");
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Ubuntu");

    vector_insert(vec, 3, "Elementary");

    ck_assert(vector_size(vec) == 4);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Elementary") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Connical") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Ubuntu") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(get_ret == NULL);

    vector_destroy(vec);
    free(vec);
}
END_TEST


START_TEST(test_vector_delete){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Connical");
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Ubuntu");
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    get_ret = strdup("Elementary");

    vector_delete(vec, 0, NULL);

    ck_assert(vector_size(vec) == 2);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Ubuntu")==0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Elementary") == 0);

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
    ck_assert(strcmp(get_ret, "Do you hear the people") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Sing, singing the song of angry") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(strcmp(get_ret, "Men, it is the music of a people who") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(strcmp(get_ret, "Will not be slaves again") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(get_ret == NULL);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Hello") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "a") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "b") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "c") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "d") == 0);

    vector_append(vec, "e");

    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Do you hear the people") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Sing, singing the song of angry") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
    ck_assert(strcmp(get_ret, "Men, it is the music of a people who") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(strcmp(get_ret, "Will not be slaves again") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(get_ret == NULL);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(strcmp(get_ret, "Hello") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(strcmp(get_ret, "a") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(strcmp(get_ret, "b") == 0 );
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(strcmp(get_ret, "c") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(strcmp(get_ret, "d") == 0);
    append_ret = vector_get(vec, 0, &get_ret);
    ck_assert_int_eq(append_ret, 0);
        ck_assert(strcmp(get_ret, "e") == 0);
    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_append_100){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    size_t i = 0;
    char buff[30];
    for(; i < 100; ++i){
        sprintf(buff, "%lu", i);
        vector_append(vec, buff);
    }
    int conglomeration = 1;
    for(i = 0; i < 100; ++i){
        sprintf(buff, "%lu", i);
        void* str;
        int append = vector_get(vec, i, &str);
        ck_assert_int_eq(append, 0);
        conglomeration &= strcmp(buff, str) == 0;
    }
    ck_assert(vector_size(vec) == 100);
    ck_assert(conglomeration);

    vector_destroy(vec);
    free(vec);
}
END_TEST

START_TEST(test_vector_append_1mil){
    void *get_ret;
    int append_ret;
    vector *vec = vector_create();

    size_t i = 0;
    char buff[30];
    for(; i < 1000000; ++i){
        sprintf(buff, "%lu", i);
        vector_append(vec, buff);
    }
    int conglomeration = 1;
    for(i = 0; i < 1000000; ++i){
        sprintf(buff, "%lu", i);
        void* str;
        int append = vector_get(vec, i, &str);
        ck_assert_int_eq(append, 0);
        conglomeration &= strcmp(buff, str) == 0;
    }
    ck_assert(vector_size(vec) == 1000000);
    ck_assert(conglomeration);

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
    ck_assert(strcmp(get_ret, "") == 0);

    vector_destroy(vec);
    free(vec);
}
END_TEST

typedef struct {
  const char *desc;
  void *test;
} test_desc;

static test_desc tests[] = {
(test_desc){"test_vector_create", test_vector_create,},
(test_desc){"test_vector_resize_larger_no_capacity", test_vector_resize_larger_no_capacity,},
(test_desc){"test_vector_resize_larger_capacity", test_vector_resize_larger_capacity,},
(test_desc){"test_vector_resize_smaller", test_vector_resize_smaller,},
(test_desc){"test_vector_resize_smaller_container", test_vector_resize_smaller_container,},
(test_desc){"test_vector_set", test_vector_set,},
(test_desc){"test_vector_get", test_vector_get,},
(test_desc){"test_vector_insert_inside", test_vector_insert_inside,},
(test_desc){"test_vector_insert_outside", test_vector_insert_outside,},
(test_desc){"test_vector_delete", test_vector_delete,},
(test_desc){"test_vector_append", test_vector_append,},
(test_desc){"test_vector_append_100", test_vector_append_100,},
(test_desc){"test_vector_append_1mil", test_vector_append_1mil,},
(test_desc){"test_vector_append_empty", test_vector_append_empty,},
(test_desc){"test_simple", test_simple,},
};

START_SUITE(vector_suite) {
  void *get_ret;
  int append_ret;
  Suite *s = suite_create("Vector Suite");
  for (int i = 0; i < sizeof(tests)/ sizeof(tests[0]); ++i) {
    test_desc *test = tests + i;
    TCase *tc_core = tcase_create(test->desc);
    tcase_add_test(tc_core, test->test);
    suite_add_tcase(s, tc_core);
  }

  return s;
}
