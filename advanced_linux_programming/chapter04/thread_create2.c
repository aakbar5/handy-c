// Listing 4.2 (thread-create2) Create Two Threads
// - Pass data to each of each thread

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

struct thread_data {
  int count;
  char tag;
};

// Thread callback
static void* tid_callback(void *arg)
{
  int i;
  struct thread_data *data = (struct thread_data *) arg;

  printf("pthread callback is starting...\n");

  for (i = 0; i < data->count; ++i) {
    printf("%c: %d\n", data->tag, i);
    usleep(100);
  }

  printf("pthread callback is ending...\n");
  return NULL;
}

//
// App entry point
//
int main()
{
  pthread_t tid1;
  pthread_t tid2;

  struct thread_data data1 = { 10, 'X' };
  struct thread_data data2 = { 15, 'Y' };

  printf("main -- create pthreads...\n");
  int ret =  pthread_create(&tid1, NULL, tid_callback, (void *)&data1);
  check_status(ret == 0, "Fail to create a pthread");

  ret =  pthread_create(&tid2, NULL, tid_callback, (void *)&data2);
  check_status(ret == 0, "Fail to create a pthread");

  printf("main -- join pthreads until those are not finished...\n");
  ret =  pthread_join(tid1, NULL);
  check_status(ret == 0, "Fail to join a pthread");

  ret =  pthread_join(tid2, NULL);
  check_status(ret == 0, "Fail to join a pthread");

  printf("main -- good bye!\n");
  return 0;
}