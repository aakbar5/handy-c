// Listing 5.8 (dup2.c) Redirect Output from a Pipe with dup2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define check_status(expr, msg)                                         \
  if (!(expr)) {                                                        \
    fprintf(stderr, "%s\n", msg);                                       \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));    \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FILE__);  \
    exit(1);                                                            \
  }

// Handy function to check do wait for child process
void wait_for_child(pid_t cpid)
{
  // Wait for child process
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

    // Close write fd copy child process is having
    close(write_fd);

    // Move pipe read fd into the process stdin
    dup2(read_fd, STDIN_FILENO);

    // Let's execute sort command
    execlp("sort", "sort", NULL);
  }
  else {

    // Close read fd copy parent process is having
    close(read_fd);

    // Open write fd for file writing
    FILE *fp = fdopen(write_fd, "w");
    fprintf(fp, "1 - Hello world!\n");
    fprintf(fp, "8 - Hello world!\n");
    fprintf(fp, "3 - Hello world!\n");
    fprintf(fp, "2 - Hello world!\n");
    fflush(fp);
    fclose(fp);

    // Wait for child process
    wait_for_child(cpid);
  }

  return 0;
}
