// Listing 4.6 (critical-section.c) Protect a Bank Transaction with a Critical Section
// - Use pthread_setcancelstate for bank transcation

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

// Bank
static float bank[] = {
  250.0f,
  300.0f,
  600.0f,
};


// Thread callback
static void* tid_callback(void *arg)
{
  int old_state;
  int ret;
  int from = 0;
  int to = 1;
  float amount = 100.0f;

  printf("[From %f][To %f]\n", bank[from], bank[to]);

  ret =  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);
  check_status(ret == 0, "Fail to change pthread state");

  if (bank[from] > amount) {
    bank[from] -= amount;
    bank[to] += amount;
  }

  ret =  pthread_setcancelstate(old_state, NULL);
  check_status(ret == 0, "Fail to change pthread state");

  printf("[From %f][To %f]\n", bank[from], bank[to]);

  (void)arg;

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