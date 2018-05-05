// A mutex

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
static pthread_mutex_t mutex;
static pthread_cond_t condition;

// Function to be called for pthread
static void* thread_func(void *arg)
{
  int ret;
  printf("ID of thread is %ld\n", pthread_self());

  // Lock the mutex to access condition
  ret =  pthread_mutex_lock(&mutex);
  check_status(ret == 0, "Failed to lock mutex");

  // Wait on condition
  ret =  pthread_cond_wait(&condition, &mutex);
  check_status(ret == 0, "Failed to do wait on condition");

  // We got a signal on our condition
  {
    printf("ID of thread is %ld -- is having *signal*\n", pthread_self());
  }

  ret =  pthread_mutex_unlock(&mutex);
  check_status(ret == 0, "Failed to unlock mutex");

  printf("ID of thread is %ld -- finished\n", pthread_self());
  (void)arg;
  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  pthread_t thread1, thread2, thread3;

  printf("--- main - start\n");

  // Create a mutex
  ret =  pthread_mutex_init(&mutex, NULL);
  check_status(ret == 0, "Failed to init mutex");

  // Create a conditional variable
  ret =  pthread_cond_init(&condition, NULL);
  check_status(ret == 0, "Failed to create cv condition");

  // Create a simple pthread with default settings
  ret =  pthread_create(&thread1, NULL, thread_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  ret =  pthread_create(&thread2, NULL, thread_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  ret =  pthread_create(&thread3, NULL, thread_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  printf("Just waiting...\n");
  usleep(microseconds);

  printf("Going to send signal\n");

  // We got more than 1 threads waiting on the condition
  // so pthread_cond_signal will invoke anyone of those.
  // To invoke all waiting threads, _broadcast should be used.
  // ret =  pthread_cond_signal(&condition);
  ret =  pthread_cond_broadcast(&condition);
  check_status(ret == 0, "Failed to send signal to condition");

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread1, NULL);
  check_status(ret == 0, "Failed to join pthread");

  ret =  pthread_join(thread2, NULL);
  check_status(ret == 0, "Failed to join pthread");

  ret =  pthread_join(thread3, NULL);
  check_status(ret == 0, "Failed to join pthread");

  // Destroy mutex
  ret =  pthread_mutex_destroy(&mutex);
  check_status(ret == 0, "Failed to destroy mutex");

  // Destroy condition
  ret =  pthread_cond_destroy(&condition);
  check_status(ret == 0, "Failed to destroy condition");

  printf("--- main - end\n");
  return 0;
}
