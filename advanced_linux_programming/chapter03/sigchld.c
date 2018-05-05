// Listing 3.7 (sigchld.c) Cleaning Up Children by Handling SIGCHLD

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Variable used to monitor child process
static sig_atomic_t signal_child_is_gone = 0;

// Signal handler
static void signal_handler(int signal_number)
{
  int status;
  wait(&status);
  signal_child_is_gone = 1;

  (void)signal_number;
}

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

  while (signal_child_is_gone == 0) {
    usleep(5); /* Waiting for child process to be finished */
  }

  printf("Child process is succesfully finished\n");
  sleep(10);
  printf("Parent process is done with work\n");
}

//
// App entry point
//
int main()
{
  struct sigaction sa;
  memset(&sa, 0, sizeof (sa));
  sa.sa_handler = &signal_handler;
  sigaction(SIGCHLD, &sa, NULL);

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
