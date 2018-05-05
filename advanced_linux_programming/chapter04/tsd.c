// Listing 4.7 (tsd.c) Per-Thread Log Files Implemented with Thread-Specific Data

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

static const int file_length = 100;
static const int num_of_threads = 3;
static pthread_key_t key;

// Handy function to write data to file
static void update_log_file(char *msg)
{
  FILE *fp = pthread_getspecific(key);
  if (fp) {
    fwrite(msg, strlen(msg), sizeof(char), fp);
  }
  else {
    check_status(fp == NULL, "Fail to get data from pthread tls");
  }
}

// Pthread key dtor
static void key_dtor(void* arg)
{
  fclose((FILE *)arg);
}

// Thread callback
static void* tid_callback(void *arg)
{
  int ret, idx;
  char file_name[file_length];
  sprintf(file_name, "log-%ld.txt", pthread_self());

  FILE *fp = fopen(file_name, "w");
  if (!fp) {
    printf("Fail to open log file errno=%d\n", errno);
    printf(" - Error! %s\n", strerror(errno));
    return NULL;
  }

  ret =  pthread_setspecific(key, fp);
  check_status(ret == 0, "Fail to set data to pthread tls");

  char msg[100];
  for (idx = 0; idx < 100; ++idx) {
    sprintf(msg, "Line # %4d - %s\n", idx +1 , "Hello world");
    update_log_file(msg);
  }

  (void) arg;
  return NULL;
}

//
// App entry point
//
int main()
{
  pthread_t tid[num_of_threads];
  int ret, idx;

  ret =  pthread_key_create(&key, key_dtor);
  check_status(ret == 0, "Fail to create a pthread key");

  for (idx = 0; idx < num_of_threads; ++idx) {
    ret =  pthread_create(&tid[idx], NULL, tid_callback, NULL);
    check_status(ret == 0, "Fail to create a pthread");
  }

  for (idx = 0; idx < num_of_threads; ++idx) {
    ret =  pthread_join(tid[idx], NULL);
    check_status(ret == 0, "Fail to join a pthread");
  }

  return 0;
}
