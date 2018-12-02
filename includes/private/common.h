#pragma once

#ifdef LIBDS_PTHREAD_ENABLED
#include <pthread.h>
#endif

#ifdef LIBDS_PTHREAD_ENABLED
#define lock_if_enabled(mtx) pthread_mutex_lock(mtx)
#else
#define lock_if_enabled(mtx)
#endif

#ifdef LIBDS_PTHREAD_ENABLED
#define unlock_if_enabled(mtx) pthread_mutex_unlock(mtx)
#else
#define unlock_if_enabled(mtx)
#endif
