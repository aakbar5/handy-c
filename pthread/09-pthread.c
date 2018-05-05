// pthread_once

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
static pthread_once_t tn_once = PTHREAD_ONCE_INIT;
static pthread_once_t tx_once = PTHREAD_ONCE_INIT;

// Function to be called once for pthread
static void call_once_funcn(void)
{
  printf("***%s***\n", __func__);
}

static void call_once_funcx(void)
{
  printf("***%s***\n", __func__);
}

// Function to be called for pthread
static void* threadn_func(void *arg)
{
  int ret;
  uint64_t delay = microseconds * ((uint64_t)arg + 1);
  printf("ID of thread is %ld having delay # %ld \n", pthread_self(), delay);

  // Ask to execute once function
  ret =  pthread_once(&tn_once, call_once_funcn);
  check_status(ret == 0, "Failed to setup once function");

  usleep(delay);

  return NULL;
}

// Function to be called for pthread
static void* threadx_func(void *arg)
{
  int ret;
  uint64_t delay = microseconds * ((uint64_t)arg + 1);
  printf("ID of thread is %ld having delay # %ld \n", pthread_self(), delay);

  // Ask to execute once function
  ret =  pthread_once(&tx_once, call_once_funcx);
  check_status(ret == 0, "Failed to setup once function");

  usleep(delay);

  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  int i;
  pthread_t tn[THREAD_COUNT];
  pthread_t tx;

  printf("--- main - start\n");

  // Create a simple pthread with default settings
  for (i = 0; i < THREAD_COUNT; ++i) {
    ret =  pthread_create(&tn[i], NULL, threadn_func, (void *)(uintptr_t)i);
    check_status(ret == 0, "Failed to create pthread");
  }

  ret =  pthread_create(&tx, NULL, threadx_func, (void *)(uintptr_t)1);
  check_status(ret == 0, "Failed to create pthread");

  // Wait for pthread to finish its execution
  for (i = 0; i < THREAD_COUNT; ++i) {
    ret =  pthread_join(tn[i], NULL);
    check_status(ret == 0, "Failed to join pthread");
  }

  ret =  pthread_join(tx, NULL);
  check_status(ret == 0, "Failed to join pthread");

  printf("--- main - end\n");
  return 0;
}
