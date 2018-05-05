// Listing 4.15 (thread-pid) Print Process IDs for Threads

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

static void* tid_callback(void *arg)
{
  printf("Process Id (pthread) -- %d\n", getpid());

  (void)arg;
  return NULL;
}

/**
 * App entry point
 **/
int main()
{
  pthread_t tid;

  printf("Process Id (main)    -- %d\n", getpid());

  int ret =  pthread_create(&tid, NULL, tid_callback, NULL);
  check_status(ret == 0, "Fail to create a mutex");

  ret =  pthread_join(tid, NULL);
  check_status(ret == 0, "Fail to create a mutex");

  return 0;
}
