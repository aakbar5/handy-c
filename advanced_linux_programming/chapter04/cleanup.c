// Listing 4.8 (cleanup.c) Program Fragment Demonstrating a Thread Cleanup Handler

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define check_status(expr, msg)                                         \
  if (!(expr)) {                                                        \
    fprintf(stderr, "%s\n", msg);                                       \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));    \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FILE__);  \
    exit(1);                                                            \
  }

// Handy function to allocate memory
static void *allocate(size_t size)
{
  return malloc(size);
}

// Handy function to de-allocate memory
static void release(void *ptr)
{
  free(ptr);
}

// Pthread cleanup function
static void tid_cleanup(void* arg)
{
  printf("Doing thread cleanup...\n");
  release(arg);
}

// Thread callback
static void* tid_callback(void *arg)
{
  void *ptr = allocate(1024);

  printf("Pushing cleanup func\n");
  pthread_cleanup_push(tid_cleanup, ptr);

  /* Doing work */
  printf("Doing work...\n");
  sleep(3);

  printf("Pop cleanup func\n");

  /* Passing 1 making sure that popped func
     is executed; Passing 0 means just popped
     the function but don't execute.
     pthread_cleanup_pop() is effectively called with a
     nonzero argument when a thread either explicitly
     or implicitly calls pthread_exit() or when the
     thread accepts a cancel request. */
  pthread_cleanup_pop(1);

  (void) arg;
  return NULL;
}

//
// App entry point
//
int main()
{
  pthread_t tid;
  int ret;

  ret =  pthread_create(&tid, NULL, tid_callback, NULL);
  check_status(ret == 0, "Fail to create a pthread");

  ret =  pthread_join(tid, NULL);
  check_status(ret == 0, "Fail to join a pthread");

  return 0;
}
