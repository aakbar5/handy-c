// A Spinlock

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
static pthread_spinlock_t slock;
static uint64_t resource = 0;

// Function to be called for pthread
static void* thread_func(void *arg)
{
  uint64_t count = 0;
  int ret;
  printf("ID of thread is %ld\n", pthread_self());

  while (count++ < limit)
  {
    ret =  pthread_spin_lock(&slock);
    check_status(ret == 0, "Failed to get spinlock");
    {
      ++resource;
    }
    ret =  pthread_spin_unlock(&slock);
    check_status(ret == 0, "Failed to release spinlock");

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

  printf("--- main - start\n");

  // Create a spin lock (private one; posix allows shared one too)
  ret =  pthread_spin_init(&slock, PTHREAD_PROCESS_PRIVATE);
  check_status(ret == 0, "Failed to create spinlock");

  // Create a simple pthread with default settings
  ret =  pthread_create(&thread, NULL, thread_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  while (count++ < (limit + 5))
  {
    ret =  pthread_spin_lock(&slock);
    check_status(ret == 0, "Failed to get spinlock");
    {
      printf("Resource = %ld\n", resource);
    }
    ret =  pthread_spin_unlock(&slock);
    check_status(ret == 0, "Failed to release spinlock");

    usleep(microseconds);
  }

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread, NULL);
  check_status(ret == 0, "Failed to join pthread");

  // Destroy spin lock
  ret =  pthread_spin_destroy(&slock);
  check_status(ret == 0, "Failed to destroy spin lock");

  printf("--- main - end\n");
  return 0;
}
