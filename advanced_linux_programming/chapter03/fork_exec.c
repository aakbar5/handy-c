// Listing 3.4 (fork-exec.c) Using fork and exec together

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to be executed in the child process context
static void execute_child_process(pid_t cpid)
{
  printf("Child - Process Id:           %d\n", getpid());
  printf("Child - Process Id (Parent):  %d\n", getppid());
  printf("fork  - Process Id:           %d\n", cpid);

  char *argv[] = {
    "ls",
    "-l",
    "/",
    NULL
  };

  /* Spawn a new process */
  int ret =  execvp(argv[0], argv);

  /* Following line of code will be executed only if exec
     is having error in executing new process */
  printf("execvp is having return code is %d\n", ret);
}

// Function to be executed in the parent process context
static void execute_parent_process(pid_t cpid)
{
  printf("Parent - Process Id:          %d\n", getpid());
  printf("Parent - Process Id (Parent): %d\n", getppid());
  printf("fork  - Process Id:           %d\n", cpid);
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
