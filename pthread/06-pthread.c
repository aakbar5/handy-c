// Create a thread with cleanup handlers

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

static const uint64_t microseconds = 1000000 * 1;

struct info {
  FILE *fp;
};

// Function to be called to cleanup resources used by the pthread
static void thread_cleanup(void* arg)
{
  struct info* io = (struct info *) arg;
  printf("Cleanup is called\n");
  if (io->fp)
    fclose(io->fp);
}

// Function to be called for pthread
static void* thread_func(void *arg)
{
  struct info* io = (struct info *) arg;

  // Push resoruce cleanup
	pthread_cleanup_push(thread_cleanup, arg);

  printf("ID of thread is %ld\n", pthread_self());
  
  // Open file
  io->fp = fopen("input.txt", "r");
  check_status(io->fp != NULL, "Fail to open input file");
  // pthread_cleanup_pop(1);
  // NOTE: Can't call pthread_cleanup_pop here as it is in matching stack order 
  // so compiler will throw error. 
  // Possible solutions:
  // (1) Have a single exit point so pthread_cleanup_pop can work
  // (2) Make use of the pthread local thread storage which allows you
  //     to have function to destory the key

  usleep(microseconds);

  // Pop & execute cleanup function
  pthread_cleanup_pop(1);
  
  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  pthread_t thread;
  struct info io = {.fp = NULL};

  printf("--- main - start\n");

  // Create a simple pthread with default settings
  ret =  pthread_create(&thread, NULL, thread_func, &io);
  check_status(ret == 0, "Failed to create pthread key");

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread, NULL);
  check_status(ret == 0, "Failed to join pthread");

  printf("--- main - end\n");
  return 0;
}
