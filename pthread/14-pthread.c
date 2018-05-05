// A Recursive mutex

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define check_status(expr, msg) do {                                        \
  if (!(expr)) {                                                            \
    fprintf(stderr, "%s\n", msg);                                           \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));        \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FUNCTION__);  \
    exit(1);                                                                \
  } \
} while (0)

static const uint64_t microseconds = 1000000 * 2;
static const uint64_t limit = 10;
static pthread_mutex_t mutex;
static uint64_t resource = 0;

// Function to be called for pthread
static void* thread_func(void *arg)
{
  uint64_t count = 0;
  int ret;
  printf("ID of thread is %ld\n", pthread_self());

  while (count++ < limit)
  {
    ret =  pthread_mutex_lock(&mutex);
    check_status(ret == 0, "Failed to lock mutex");
    {
      // Re-lock the same mutex
      // NOTE: Update PTHREAD_MUTEX_RECURSIVE option with PTHREAD_MUTEX_ERRORCHECK passed to
      //       pthread_mutexattr_settype to see error on attempting
      //       to lock mutex which is already locked.
      ret =  pthread_mutex_lock(&mutex);
      check_status(ret == 0, "Failed to lock mutex");
      {
        ++resource;
      }
      ret =  pthread_mutex_unlock(&mutex);
      check_status(ret == 0, "Failed to unlock mutex");
    }
    ret =  pthread_mutex_unlock(&mutex);
    check_status(ret == 0, "Failed to unlock mutex");

    usleep(microseconds);
  }

  printf("ID of thread is %ld -- finished\n", pthread_self());
  (void)arg;
  return NULL;
}

//
// App entry point
//
int main() {
  uint64_t count = 0;
  int ret;
  pthread_t thread;
  pthread_mutexattr_t mattr;

  printf("--- main - start\n");

  // Create mutex attribute to have recursive one
  ret =  pthread_mutexattr_init(&mattr);
  check_status(ret == 0, "Failed to init mutex attr");

  // Mark mutex as a recursive
  ret =  pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
  check_status(ret == 0, "Failed to set mutex type");

  // Create a mutex
  ret =  pthread_mutex_init(&mutex, &mattr);
  check_status(ret == 0, "Failed to init mutex");

  // Create a simple pthread with default settings
  ret =  pthread_create(&thread, NULL, thread_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  while (count++ < (limit + 5))
  {
    ret =  pthread_mutex_trylock(&mutex);
    if (ret == EBUSY)
    {
      printf("Resource is busy\n");
    }
    else if (ret == 0)
    {
      printf("Resource = %ld\n", resource);

      ret =  pthread_mutex_unlock(&mutex);
      check_status(ret == 0, "Failed to unlock mutex");
    }

    usleep(microseconds);
  }

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread, NULL);
  check_status(ret == 0, "Failed to join pthread");

  // Destroy mutex
  ret =  pthread_mutex_destroy(&mutex);
  check_status(ret == 0, "Failed to destroy mutex");

  // Destroy mutex attr
  ret =  pthread_mutexattr_destroy(&mattr);
  check_status(ret == 0, "Failed to destroy mutex attr");

  printf("--- main - end\n");
  return 0;
}
