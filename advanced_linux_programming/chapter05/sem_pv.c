// Listing 5.4 (sem_pv.c) Wait and Post Operations for a Binary Semaphore

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "psem.h"

#define check_status(expr, msg)                                         \
  if (!(expr)) {                                                        \
    fprintf(stderr, "%s\n", msg);                                       \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));    \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FILE__);  \
    exit(1);                                                            \
  }

static int sema_id;
static const int sema_key = 555;
static const int message_limit = 20;

// Handy function to check do wait for child process
void wait_for_child(pid_t cpid)
{
  /* Wait for child process */
  int status;
  pid_t wpid;

  while (1) {
    wpid = waitpid(cpid, &status, WNOHANG | WUNTRACED);
    if (wpid == -1) {
      printf("Fail to to wait for pid # %d\n", cpid);
      return;
    }

    if (WIFSTOPPED(status)) {
      printf("pid # %d is having stopped(status=%d)\n", cpid, WSTOPSIG(status));
      return;
    }
    else if (WIFEXITED(status)) {
      printf("pid # %d is having exited(status=%d)\n", cpid, WEXITSTATUS(status));
      return;
    }
    else if (WIFSIGNALED(status)) {
      printf("pid # %d is having killed(status=%d)\n", cpid, WTERMSIG(status));
      return;
    }
  }
}

// Function to be executed in the child process context
void execute_child_process(pid_t cpid)
{
  int ret;
  int count = 0;

  sleep(2);
  printf("Child - Process Id:           %d\n", getpid());
  printf("Child - Process Id (Parent):  %d\n", getppid());
  printf("fork  - Process Id:           %d\n", cpid);

  while (count < message_limit)
  {
    ret =  psem_wait(sema_id);
    if (ret != 0)
      printf("---> Fail to wait sema (err # %d)\n", ret);

    printf("Child  -- message (%d) is received\n", count);
    ++count;
  }

  printf("******* Child process is ending ***** \n");
}

// Function to be executed in the parent process context
void execute_parent_process(pid_t cpid)
{
  int ret;
  int count = 0;

  printf("Parent - Process Id:          %d\n", getpid());
  printf("Parent - Process Id (Parent): %d\n", getppid());
  printf("fork   - Process Id:          %d\n", cpid);

  while (count < message_limit)
  {
    printf("Parent -- message (%d) is sent\n", count);
    ret =  psem_post(sema_id);
    check_status(ret == 0, "Fail to post sema");

    count++;
    sleep(2);
  }

  printf("******* Parent process is ending ***** \n");

  // Wait for child process
  printf("Parent - Wait for child process\n");
  wait_for_child(cpid);

  // Destroy semaphore
  printf("Parent - Destroy semaphore\n");
  ret =  psem_destroy(sema_id);
  check_status(ret == 0, "Fail to destroy sema");
}

//
// App entry point
//
int main()
{
  int ret;

  // Setup semaphore
  ret =  psem_open(sema_key, &sema_id);
  if (ret != 0)
    printf("Use `ipcrm -S %d` to remove old semaphore\n", sema_key);
  check_status(ret == 0, "Fail to create sema");

  printf("Main - Process Id:            %d\n", getpid());
  printf("Main - Process Id (Parent):   %d\n", getppid());

  // Setup child process
  pid_t cpid = fork();
  if (cpid == -1) {
    printf("Fail to fork process\n");
  }
  else if (cpid == 0) {
    execute_child_process(cpid);
  }
  else {
    execute_parent_process(cpid);
  }

  printf("Main - Good bye!\n");

  return 0;
}
