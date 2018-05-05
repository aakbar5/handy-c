// Create a thread, pass an argument and
// reterieve status once it is finished

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define check_status(expr, msg) do {                                          \
  if (!(expr)) {                                                              \
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
  printf("Arg of thread is %s\n", (char *)arg);

  // Do an important work
  usleep(microseconds);

  // return exit code
  pthread_exit((void *)5);
  // return ((void *)5);
}

//
// App entry point
//
int main() {
  int ret;
  int thread_sts = -1;
  pthread_t thread;

  printf("--- main - start\n");

  // Create a pthread and sends an argument
  ret =  pthread_create(&thread, NULL, thread_func, "hello");
  check_status(ret == 0, "Failed to create pthread");

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread, (void *)&thread_sts);
  check_status(ret == 0, "Failed to join pthread");
  printf("Thread is finished with ret: %d\n", thread_sts);

  printf("--- main - end\n");
  return 0;
}
