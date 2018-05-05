// Listing 4.9 (cxx-exit.cpp) Implementing Safe Thread Exit with C++ Exceptions

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

// Exception error code
static int exception_error = -200;

// Exception class
class pthread_exit_exception {
public:
  void *return_code_;
  pthread_exit_exception(void *ret): return_code_(ret) {}
};

// Thread callback
static void* tid_callback(void *arg)
{
  try {

    /* Doing work */
    printf("Doing work...\n");
    sleep(1);

    throw pthread_exit_exception((void *) &exception_error);
  }
  catch(const pthread_exit_exception& ex) {
    std::cout << "Exception is caught (ex)" << "\n";
    pthread_exit(ex.return_code_);
  }
  catch (...) {
    std::cout << "Exception is caught (NULL)" << "\n";
    pthread_exit(NULL);
  }

  (void) arg;
  return NULL;
}

//
// App entry point
//
int main()
{
  pthread_t tid;
  int ret;
  void *return_code;

  ret =  pthread_create(&tid, NULL, tid_callback, NULL);
  check_status(ret == 0, "Fail to create a pthread");

  ret =  pthread_join(tid, &return_code);
  check_status(ret == 0, "Fail to join a pthread");

  if (return_code)
    printf("Pthread is ended up with return code # %d\n", *((int *)return_code));
  else
    printf("Pthread is ended up with no return code\n");

  return 0;
}
