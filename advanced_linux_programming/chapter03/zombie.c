// Listing 3.6 (zombie.c) Making a Zombie Process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to be executed in the child process context
static void execute_child_process(pid_t cpid)
{
  printf("Child - Process Id:           %d\n", getpid());
  printf("Child - Process Id (Parent):  %d\n", getppid());
  printf("fork  - Process Id:           %d\n", cpid);
  exit(0);
}

// Function to be executed in the parent process context
static void execute_parent_process(pid_t cpid)
{
  printf("Parent - Process Id:          %d\n", getpid());
  printf("Parent - Process Id (Parent): %d\n", getppid());
  printf("fork  - Process Id:           %d\n", cpid);

  /* Parent process is busy in doing its work */
  /* During this period child process will be marked
     zombie if child process has finished it's work */
  sleep(100);
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

  printf("Good bye from the main!\n");

  return 0;
}