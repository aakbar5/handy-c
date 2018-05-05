// Create a thread with custom attributes (stack size)

#define _GNU_SOURCE
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

// Function to be called for pthread
static void* thread_func(void *arg)
{
  int ret;
  int val;
  size_t size;
  struct sched_param sp;
  pthread_attr_t attr;
  pthread_t tid = pthread_self();

  printf("ID of thread is %ld\n", tid);

  // Non standard API to retereive attribute
  // otherwise stores original used during creation
  ret =  pthread_getattr_np(tid, &attr);
  check_status(ret == 0, "Failed to reterieve attribute");

  ret =  pthread_attr_getschedparam(&attr, &sp);
  check_status(ret == 0, "Failed to get sched attribute");
  printf("%ld: Scheduling priority = %d\n", tid, sp.sched_priority);

  ret =  pthread_attr_getschedpolicy(&attr, &val);
  check_status(ret == 0, "Failed to get policy attribute");
  printf("%ld: Scheduling policy = %s\n", tid,
    val == SCHED_OTHER ? "SCHED_OTHER" :
    val == SCHED_FIFO ? "SCHED_FIFO" :
    val == SCHED_RR ? "SCHED_RR" : "??");

  ret =  pthread_attr_getinheritsched(&attr, &val);
  check_status(ret == 0, "Failed to get inherit sched attribute");
  printf("%ld: Inherit scheduler = %s\n", tid,
    val == PTHREAD_INHERIT_SCHED ? "PTHREAD_INHERIT_SCHED" :
    val == PTHREAD_EXPLICIT_SCHED ? "PTHREAD_EXPLICIT_SCHED" : "??");

  ret =  pthread_attr_getscope(&attr, &val);
  check_status(ret == 0, "Failed to get scope attribute");
  printf("%ld: Scope = %s\n", tid,
    val == PTHREAD_SCOPE_SYSTEM ? "PTHREAD_SCOPE_SYSTEM" :
    val == PTHREAD_SCOPE_PROCESS ? "PTHREAD_SCOPE_PROCESS" : "??");

  // Deprecated API
  // {
  //   void *addr;
  //   ret =  pthread_attr_getstackaddr(&attr, &addr);
  //   check_status(ret == 0, "Failed to get stack address");
  //   printf("%ld: Stack addr = %p bytes\n", tid, addr);
  // }

  ret =  pthread_attr_getstacksize(&attr, &size);
  check_status(ret == 0, "Failed to get stack size");
  printf("%ld: Stack size = %zu bytes\n", tid, size);

  ret =  pthread_attr_getdetachstate(&attr, &val);
  check_status(ret == 0, "Failed to get detach state");
  printf("%ld: Detach = %s\n", tid,
    val == PTHREAD_CREATE_DETACHED ? "PTHREAD_CREATE_DETACHED" :
    val == PTHREAD_CREATE_JOINABLE ? "PTHREAD_CREATE_JOINABLE" : "??");

  ret =  pthread_attr_getguardsize(&attr, &size);
  check_status(ret == 0, "Failed to get gard size");
  printf("%ld: Guard size = %zu bytes\n", tid, size);

  (void)arg;

  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  pthread_t thread1;
  pthread_t thread2;
  pthread_attr_t attr;

  printf("--- main - start\n");

  // Thread with default attributes
  ret =  pthread_create(&thread1, NULL, thread_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  // Create attributes handle
  ret =  pthread_attr_init(&attr);
  check_status(ret == 0, "Failed to init attribute");

  // Mark thread as detach
  ret =  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  check_status(ret == 0, "Failed to set detach attribute");

  // Thread with custom attributes
  ret =  pthread_create(&thread2, &attr, thread_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  // Check status of detach thread
  // pthread_tryjoin_np is non-portable API to check status of a thread
  ret =  pthread_join(thread2, NULL);
  if (ret == EINVAL)
    printf("Checking status [thread2]: %d(%s)\n", ret, "No joinable");
  else
    printf("Checking status [thread2]: %d(%s)\n", ret, strerror(errno));

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread1, NULL);
  printf("Checking status [thread1]: %d(%s)\n", ret, strerror(errno));

  // Destroy an attribute
  // Is it safe to do here as detach thread can be in execution?
  ret =  pthread_attr_destroy(&attr);
  check_status(ret == 0, "Failed to destroy attribute");

  printf("--- main - end\n");
  return 0;
}
