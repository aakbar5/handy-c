// Listing 5.7 (pipe.c) Using a Pipe to Communicate with a Child Process

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

static const int message_limit = 10;
static const char *test_msg = "Hello world!";

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
void execute_child_process(pid_t cpid, int read_fd)
{
  const int length = 512;
  char buffer[length];

  printf("Child - Process Id:           %d\n", getpid());
  printf("Child - Process Id (Parent):  %d\n", getppid());
  printf("fork  - Process Id:           %d\n", cpid);

  FILE *fp = fdopen(read_fd, "r");
  while (fgets(buffer, length, fp) != NULL &&
       !feof(fp) && !ferror(fp))
  {
    fputs(buffer, stdout); // printf uses buffered approach for messages

    strcpy(buffer, "");
  }

  fclose(fp);
  printf("******* Child process is ending ***** \n");
}

// Function to be executed in the parent process context
void execute_parent_process(pid_t cpid, int write_fd)
{
  int count = 0;
  const int length = 512;
  char buffer[length];

  printf("Parent - Process Id:          %d\n", getpid());
  printf("Parent - Process Id (Parent): %d\n", getppid());
  printf("fork   - Process Id:          %d\n", cpid);

  FILE *fp = fdopen(write_fd, "w");

  while (count < message_limit)
  {
    sprintf(buffer, "%d -- %s", count, test_msg);
    fprintf(fp, "%s\n", buffer);
    fflush(fp);
    ++count;
  }

  printf("******* Parent process is ending ***** \n");

  // Wait for child process
  printf("Parent - Wait for child process\n");
  wait_for_child(cpid);
}

//
// App entry point
//
int main()
{
  int ret;

  int pipe_fds[2];
  ret =  pipe(pipe_fds);
  check_status(ret == 0, "Fail to create pipe");

  int read_fd = pipe_fds[0];
  int write_fd = pipe_fds[1];

  printf("Main - Process Id:            %d\n", getpid());
  printf("Main - Process Id (Parent):   %d\n", getppid());

  // Setup child process
  pid_t cpid = fork();
  if (cpid == -1) {
    printf("Fail to fork process\n");
  }
  else if (cpid == 0) {
    close(write_fd);
    execute_child_process(cpid, read_fd);
  }
  else {
    close(read_fd);
    execute_parent_process(cpid, write_fd);
  }

  printf("Main - Good bye!\n");

  return 0;
}
