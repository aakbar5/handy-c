// A thread with thread specific data

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

// Pthread key dtor
static void key_dtor(void* arg)
{
  printf("pthead destroy dtor...\n");
  fclose((FILE *)arg);
}

// Function to be called for pthread
static void* thread_func(void *arg)
{
  int ret;
  pthread_key_t key = (pthread_key_t) (uintptr_t)arg;

  printf("ID of thread is %ld\n", pthread_self());

  FILE *fp = fopen("input.txt", "r");
  check_status(fp != NULL, "Fail to open input file");

  ret =  pthread_setspecific(key, fp);
  check_status(ret == 0, "Fail to set data to pthread tls");

  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  pthread_t thread;
  pthread_key_t key;

  printf("--- main - start\n");

  // Create pthread key
  ret =  pthread_key_create(&key, key_dtor);
  check_status(ret == 0, "Failed to create pthread key");

  // Create a simple pthread with default settings
  ret =  pthread_create(&thread, NULL, thread_func, (void *)(uintptr_t)key);
  check_status(ret == 0, "Failed to create pthread");

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread, NULL);
  check_status(ret == 0, "Failed to join pthread");

  printf("--- main - end\n");
  return 0;
}
