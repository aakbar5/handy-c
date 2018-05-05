// Listing 4.12 (job-queue3.c) Job Queue Controlled by a Semaphore

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

#define check_status(expr, msg)                                         \
  if (!(expr)) {                                                        \
    fprintf(stderr, "%s\n", msg);                                       \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));    \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FILE__);  \
    exit(1);                                                            \
  }

struct job_ {
  void *data;  /* User data */
  uint32_t id; /* Job id */
  struct job_* next; /* Point to the next job */
};

// Job queue
static struct job_ *job_queue = NULL;
static pthread_mutex_t job_queue_mutex = {0};
static sem_t job_queue_sema = {0};

// Return the count of the jobs in the list
static uint32_t get_job_count()
{
  struct job_ *last_job = job_queue;
  uint32_t count = 0;
  while (last_job)
  {
    ++count;
    last_job = last_job->next;
  }

  return count;
}

// Show all jobs
static void show_jobs()
{
  printf("Job Count # %d\n", get_job_count());

  struct job_ *last_job = job_queue;
  while (last_job)
  {
    printf("Job Id # %d\n", last_job->id);
    last_job = last_job->next;
  }
}

// Push a job to the list
static int push_job(void *data)
{
  int ret;

  struct job_ *job = malloc(sizeof(struct job_));
  if (!job) {
    return -1;
  }

  ret =  pthread_mutex_lock(&job_queue_mutex);
  check_status(ret == 0, "Fail to lock a mutex");

  job->id = get_job_count() + 1;
  job->data = data;

  if (job_queue) {
    job->next = job_queue;
  }
  else {
    job->next = NULL;
  }

  job_queue = job;

  ret =  pthread_mutex_unlock(&job_queue_mutex);
  check_status(ret == 0, "Fail to unlock a mutex");

  return 0;
}

// Pop up a job from the list
static int pop_job(uint32_t *id, void **data)
{
  struct job_ *job = job_queue;
  int ret;

  if (job) {

    ret =  pthread_mutex_lock(&job_queue_mutex);
    check_status(ret == 0, "Fail to lock a mutex");

    job_queue = job_queue->next;
    if (id) *id = job->id;
    if (data) *data = job->data;

    ret =  pthread_mutex_unlock(&job_queue_mutex);
    check_status(ret == 0, "Fail to unlock a mutex");

    free(job);

    return 0;
  }

  return -1;
}

// Thread # producer
static void* producer_callback(void *arg)
{
  int ret;

  while (1)
  {
    uint32_t job_id;
    if (pop_job(&job_id, NULL) == 0) {
      printf("Got Job # %d\n", job_id);
    }

    ret =  sem_wait(&job_queue_sema);
    check_status(ret == 0, "Fail to wait on a sema");
  }

  (void)arg;
  return NULL;
}

// Thread # consumer
static void* consumer_callback(void *arg)
{
  int ret;

  while (1)
  {
    ret =  push_job(NULL);
    if (ret == 0) {
      ret =  sem_post(&job_queue_sema);
      check_status(ret == 0, "Fail to post a sema");

      printf("Job is pushed\n");
    }
    else {
      printf("Error! can not push a job\n");
    }

    sleep(1);
  }

  (void)arg;
  return NULL;
}

//
// App entry point
//
int main()
{
  pthread_t producer_thread;
  pthread_t consumer_thread;

  printf("Show available jobs: \n");
  show_jobs();

  int ret =  pthread_mutex_init(&job_queue_mutex, NULL);
  check_status(ret == 0, "Fail to create a mutex");

  ret =  sem_init(&job_queue_sema, 0, 0);
  check_status(ret == 0, "Fail to create a sema");

  ret =  pthread_create(&producer_thread, NULL, producer_callback, NULL);
  check_status(ret == 0, "Fail to create a pthread");

  ret =  pthread_create(&consumer_thread, NULL, consumer_callback, NULL);
  check_status(ret == 0, "Fail to create a pthread");

  ret =  pthread_join(producer_thread, NULL);
  check_status(ret == 0, "Fail to join a pthread");

  ret =  pthread_join(consumer_thread, NULL);
  check_status(ret == 0, "Fail to join a pthread");

  return 0;
}
