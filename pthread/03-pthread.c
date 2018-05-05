// Create a detach thread

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

static const uint64_t microseconds = 1000000 * 5;

// Function to be called for pthread
static void* thread_func(void *arg)
{
  printf("ID of thread is %ld\n", pthread_self());
  printf("Arg of thread is %s\n", (char *)arg);

  // Do an important work
  usleep(microseconds);

  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  pthread_t thread1;
  pthread_t thread2;

  printf("--- main - start\n");

  // Create a pthread and sends an argument
  ret =  pthread_create(&thread1, NULL, thread_func, "joinable");
  check_status(ret == 0, "Failed to create pthread");

  ret =  pthread_create(&thread2, NULL, thread_func, "detach");
  check_status(ret == 0, "Failed to create pthread");

  // Mark a thread as a detach
  ret =  pthread_detach(thread2);
  check_status(ret == 0, "Failed mark thread as a detach");

  // Check status of detach thread
  // pthread_tryjoin_np is non-portable API to check status of a thread
  ret =  pthread_join(thread2, NULL);
  if (ret == EINVAL)
    printf("Checking status [thread2]: %d(%s)\n", ret, "No joinable");
  else
    printf("Checking status [thread2]: %d(%s)\n", ret, strerror(errno));

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread1, NULL);
  printf("Checking status [thread1]: %d(%s)\n", ret, strerror(errno));

  printf("--- main - end\n");
  return 0;
}
