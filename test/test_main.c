#include "test_common.h"

extern void * __start_tests_;
extern void * __stop_tests_;

int main(void) {
    UnitTest *start = (UnitTest *)&__start_tests_;
    UnitTest *end = (UnitTest *)&__stop_tests_;
    int ret = 0;
    for (size_t i = 0; i < end - start; ++i) {
      Suite *s = start[i].func();
      SRunner *sr = srunner_create(s);
      srunner_run_all(sr, CK_NORMAL);
      int number_failed = srunner_ntests_failed(sr);
      srunner_free(sr);
      ret |= number_failed;
	  }
    return !!ret;
}
