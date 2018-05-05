// A barrier
// There are 4 different threads which does their own
// and then do wait on barrier to make sure that everyone
// has reached to a common point.

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

#define THREAD_COUNT  4
static const uint64_t microseconds = 1000000 * 2;
static pthread_barrier_t barrier;

// Function to be called for pthread
static void* thread_func(void *arg)
{
  uint64_t delay = microseconds * ((uint64_t)arg + 1);
  printf("ID of thread is %ld having delay # %ld \n", pthread_self(), delay);
  usleep(delay);

  printf("ID of thread is %ld is waiting for barrier\n", pthread_self());
  pthread_barrier_wait(&barrier);

  printf("ID of thread is %ld is back after barrier\n", pthread_self());

  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  int i;
  pthread_t thread[THREAD_COUNT];

  printf("--- main - start\n");

  // Create a barrier for threads
  ret =  pthread_barrier_init(&barrier, NULL, THREAD_COUNT);

  // Create a simple pthread with default settings
  for (i = 0; i < THREAD_COUNT; ++i) {
    ret =  pthread_create(&thread[i], NULL, thread_func, (void *)(uintptr_t)i);
    check_status(ret == 0, "Failed to create pthread");
  }

  // Wait for pthread to finish its execution
  for (i = 0; i < THREAD_COUNT; ++i) {
    ret =  pthread_join(thread[i], NULL);
    check_status(ret == 0, "Failed to join pthread");
  }

  // Destroy barrier
  ret =  pthread_barrier_destroy(&barrier);
  check_status(ret == 0, "Failed to destroy barrier");

  printf("--- main - end\n");
  return 0;
}
