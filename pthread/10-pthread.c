// pthread_kill - Send signal to a thread

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define check_status(expr, msg) do {                                        \
  if (!(expr)) {                                                            \
    fprintf(stderr, "%s\n", msg);                                           \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));        \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FUNCTION__);  \
    exit(1);                                                                \
  } \
} while (0)

static const uint64_t microseconds = 1000000 * 3;

// Function to be called for pthread
static void* thread_func(void *arg)
{
  sigset_t s_set;
  int ret;
  int sig;

  sigfillset(&s_set);
  pthread_sigmask(SIG_BLOCK, &s_set, NULL);

  sigemptyset(&s_set);
  sigaddset(&s_set, SIGUSR1);
  sigaddset(&s_set, SIGTSTP);
  sigaddset(&s_set, SIGQUIT);
  sigaddset(&s_set, SIGKILL);

  printf("ID of thread is %ld\n", pthread_self());

  while(1)
  {
    ret =  sigwait(&s_set, &sig);
    check_status(ret == 0, "Failed to do signal wait");

    switch (sig)
    {
    case SIGUSR1:
      printf("Signal # SIGUSR1 is received\n");
      break;

    case SIGTSTP:
      printf("Signal # SIGTSTP is received\n");
      break;

    case SIGQUIT:
      printf("Signal # SIGQUIT is received\n");
      break;

    default:
      printf("Default handler for signal: %d\n", sig);
      break;
    }
  }

  usleep(microseconds);
  (void)arg;

  return NULL;
}

//
// App entry point
//
int main() {
  int ret;
  pthread_t thread;

  printf("--- main - start\n");

  // Create a simple pthread with default settings
  ret =  pthread_create(&thread, NULL, thread_func, NULL);
  check_status(ret == 0, "Failed to create pthread");

  // Send signal to thread
  usleep(microseconds);
  printf("Sending signal # SIGUSR1\n");
  ret =  pthread_kill(thread, SIGUSR1);
  check_status(ret == 0, "Failed to send signal # SIGUSR1");

  usleep(microseconds);
  printf("Sending signal # 0\n");
  ret =  pthread_kill(thread, 0);
  check_status(ret == 0, "Failed to send signal # 0");

  usleep(microseconds);
  printf("Sending signal # SIGTSTP\n");
  ret =  pthread_kill(thread, SIGTSTP);
  check_status(ret == 0, "Failed to send signal # SIGTSTP");

  usleep(microseconds);
  printf("Sending signal # SIGQUIT\n");
  ret =  pthread_kill(thread, SIGQUIT);
  check_status(ret == 0, "Failed to send signal # SIGQUIT");

  usleep(microseconds);
  printf("Sending signal # SIGKILL\n");
  ret =  pthread_kill(thread, SIGKILL);
  check_status(ret == 0, "Failed to send signal # SIGKILL");

  // Wait for pthread to finish its execution
  ret =  pthread_join(thread, NULL);
  check_status(ret == 0, "Failed to join pthread");

  printf("--- main - end\n");
  return 0;
}
