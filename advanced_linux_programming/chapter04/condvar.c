// Listing 4.14 (condvar.c) Control a Thread Using a Condition Variable

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

static pthread_mutex_t mutex = {0};
static pthread_cond_t cond = {0};
static uint64_t done = 0;

// Thread callback
static void* inc_counter(void *arg)
{
  int number = (intptr_t)arg;
  int ret;

  while (1) {
    ret =  pthread_mutex_lock(&mutex);
    check_status(ret == 0, "Fail to lock a mutex");

    done++;
    printf("thread %2d having done %ld\n", number, done);

    // Wakeup suspended/sleeping tasks
    ret =  pthread_cond_signal(&cond);
    check_status(ret == 0, "Fail to signal a cond");

    ret =  pthread_mutex_unlock(&mutex);
    check_status(ret == 0, "Fail to unlock a mutex");

    usleep(10 * number);
  }

  (void)arg;
  return NULL;
}

// Thread callback
static void* show_counter(void *arg)
{
  int ret;

  while (1) {
    ret =  pthread_mutex_lock(&mutex);
    check_status(ret == 0, "Fail to lock a mutex");

    ret =  pthread_cond_wait(&cond, &mutex);
    check_status(ret == 0, "Fail to wait on cond");

    printf("Print this message (done=%ld)\n", done);

    ret =  pthread_mutex_unlock(&mutex);
    check_status(ret == 0, "Fail to unlock a mutex");
  }

  (void)arg;
  return NULL;
}

/*
 * App entry point
 */
int main()
{
  int idx;
  pthread_t tids[3];

  int ret =  pthread_mutex_init(&mutex, NULL);
  check_status(ret == 0, "Fail to create a mutex");

  ret =  pthread_cond_init(&cond, NULL);
  check_status(ret == 0, "Fail to create a cond");

  ret =  pthread_create(&tids[0], NULL, show_counter, (void *)0);
  check_status(ret == 0, "Fail to create a pthread");

  ret =  pthread_create(&tids[1], NULL, inc_counter, (void *)1);
  check_status(ret == 0, "Fail to create a pthread");

  ret =  pthread_create(&tids[2], NULL, inc_counter, (void *)2);
  check_status(ret == 0, "Fail to create a pthread");

  for (idx = 0; idx < 3; ++idx) {
    ret =  pthread_join(tids[idx], NULL);
    check_status(ret == 0, "Fail to join a pthread");
  }

  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutex);

  return 0;
}
