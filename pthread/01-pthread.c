// Create a thread

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

static const uint64_t microseconds = 1000000 * 3;

// Function to be called for pthread
static void* thread_func(void *arg)
{
  printf("ID of thread is %ld\n", pthread_self());
  usleep(microseconds);

  (void)arg;

  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  pthread_t thread;

  printf("--- main - start\n");

  // Create a simple pthread with default settings
  ret =  pthread_create(&thread, NULL, thread_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread, NULL);
  check_status(ret == 0, "Failed to join pthread");

  printf("--- main - end\n");
  return 0;
}
