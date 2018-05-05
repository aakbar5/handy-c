// Listing 4.1 (thread-create.c) Create a Thread

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

// Thread callback
static void* tid_callback(void *arg)
{
  int i;

  printf("pthread callback is starting...\n");

  for (i = 0; i < 1000; ++i) {
    printf("%d ", i);
    usleep(100);
  }

  printf("pthread callback is ending...\n");
  (void)arg;

  return NULL;
}

//
// App entry point
//
int main()
{
  pthread_t tid;

  printf("main -- create a pthread...\n");
  int ret =  pthread_create(&tid, NULL, tid_callback, NULL);
  check_status(ret == 0, "Fail to create a pthread");

  printf("main -- join it until it is not finished...\n");
  ret =  pthread_join(tid, NULL);
  check_status(ret == 0, "Fail to join a pthread");

  printf("main -- good bye!\n");
  return 0;
}
