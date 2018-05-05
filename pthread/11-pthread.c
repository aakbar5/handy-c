// x2 Threads + Semaphore

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define check_status(expr, msg) do {                                        \
  if (!(expr)) {                                                            \
    fprintf(stderr, "%s\n", msg);                                           \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));        \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FUNCTION__);  \
    exit(1);                                                                \
  } \
} while (0)

static const uint64_t microseconds = 1000000 * 3;
static uint64_t count = 0;
static sem_t sema = {0};

// Function to be called for pthread
static void* thread1_func(void *arg)
{
  int ret;

  printf("ID of thread is %ld\n", pthread_self());

  while (count < 10)
  {
    ret =  sem_wait(&sema);
    check_status(ret == 0, "Failed to wait on a sema");

    printf("Semaphore signal is recevied (%ld)\n", count);
    ++count;

    usleep(microseconds);
  }

  (void)arg;

  return NULL;
}

// Function to be called for pthread
static void* thread2_func(void *arg)
{
  int ret;

  printf("ID of thread is %ld\n", pthread_self());

  while (count < 10)
  {
    ret =  sem_post(&sema);
    check_status(ret == 0, "Failed to post a sema");

    usleep(microseconds);
  }

  (void)arg;

  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  pthread_t thread1, thread2;

  printf("--- main - start\n");

  // Create a semaphore
  ret =  sem_init(&sema, 0, 0);
  check_status(ret == 0, "Failed to create a sema");

  // Create a simple pthread with default settings
  ret =  pthread_create(&thread1, NULL, thread1_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  // Create a simple pthread with default settings
  ret =  pthread_create(&thread2, NULL, thread2_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread1, NULL);
  check_status(ret == 0, "Failed to join pthread");

  ret =  pthread_join(thread2, NULL);
  check_status(ret == 0, "Failed to join pthread");

  printf("--- main - end\n");
  return 0;
}
