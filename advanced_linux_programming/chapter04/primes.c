// Listing 4.4 ( primes.c) Compute Prime Numbers in a Thread
// Compute successive prime numbers (very inefficiently). Return the
// Nth prime number, where N is the value pointed to by *ARG.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// Thread callback
static void* tid_callback(void *arg)
{
  int number = *((int *) arg);
  int i, j;
  int prime_count = 1;
  int is_prime = 0;

  for (i = 2; i < number; ++i)
  {
    if (number % i == 0) // we have factor
    {
      is_prime = 1;
      for (j = 2; j < i / 2; ++j)
      {
        if (j % i == 0) {
          is_prime = 0;
          break;
        }
      }

      if (is_prime == 1) {
        ++prime_count;
      }
    }
  }

  return (void *) (intptr_t) prime_count;
}

//
// App entry point
//
int main()
{
  pthread_t tid;
  int number = 200;
  int prime_count;

  int ret =  pthread_create(&tid, NULL, tid_callback, (void *)&number);
  check_status(ret == 0, "Fail to create a pthread");

  ret =  pthread_join(tid, (void *)&prime_count);
  check_status(ret == 0, "Fail to join a pthread");

  printf("%4d is having %4d prime factors\n", number, prime_count);

  return 0;
}