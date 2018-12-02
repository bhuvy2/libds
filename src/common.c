#include "common.h"
#include <stdlib.h>

extern int pthread_create () __attribute__((weak));

int pthread_linked() {
  return pthread_create != NULL;
}
