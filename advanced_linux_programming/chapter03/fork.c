// Listing 3.3 (fork.c) Using fork to Duplicate a Program’s Process

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to be executed in the child process context
void execute_child_process(pid_t cpid)
{
  printf("Child - Process Id:           %d\n", getpid());
  printf("Child - Process Id (Parent):  %d\n", getppid());
  printf("fork  - Process Id:           %d\n", cpid);
}

// Function to be executed in the parent process context
void execute_parent_process(pid_t cpid)
{
  printf("Parent - Process Id:          %d\n", getpid());
  printf("Parent - Process Id (Parent): %d\n", getppid());
  printf("fork   - Process Id:          %d\n", cpid);

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

//
// App entry point
//
int main()
{
  printf("Main - Process Id:            %d\n", getpid());
  printf("Main - Process Id (Parent):   %d\n", getppid());

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