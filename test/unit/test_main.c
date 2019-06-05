#include "test_common.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern void * __start_tests_;
extern void * __stop_tests_;

char *target_suite = NULL;

void parse_args(int argc, char *argv[]) {
  int opt;

  while ((opt = getopt(argc, argv, "s:")) != -1) {
    switch (opt) {
    case 's':
      target_suite = optarg;
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-s suite]\n",
              argv[0]);
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char *argv[]) {
  parse_args(argc, argv);
    UnitTest *start = (UnitTest *)&__start_tests_;
  UnitTest *end = (UnitTest *)&__stop_tests_;
  int ret = 0;
  for (size_t i = 0; i < end - start; ++i) {
    Suite *s = start[i].func();
    if (target_suite != NULL && strcmp(target_suite, (char*)s) != 0) {
      continue;
    }
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    ret |= number_failed;
  }
  return !!ret;
}
