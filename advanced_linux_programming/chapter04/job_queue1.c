// Listing 4.10 ( job-queue1.c) Thread Function to Process Jobs from the Queue

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

struct job_ {
  void *data;  /* User data */
  uint32_t id; /* Job id */
  struct job_* next; /* Point to the next job */
};

// Job queue
static struct job_ *job_queue = NULL;

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
  struct job_ *job = malloc(sizeof(struct job_));
  if (!job) {
    return -1;
  }

  job->id = get_job_count() + 1;
  job->data = data;

  if (job_queue) {
    job->next = job_queue;
  }
  else {
    job->next = NULL;
  }

  job_queue = job;

  return 0;
}

// Pop up a job from the list
static int pop_job(uint32_t *id, void **data)
{
  struct job_ *job = job_queue;

  if (job) {
    job_queue = job_queue->next;
    if (id) *id = job->id;
    if (data) *data = job->data;
    free(job);

    return 0;
  }

  return -1;
}

// Thread callback
static void* tid_callback(void *arg)
{
  while (1)
  {
    uint32_t job_id;
    if (pop_job(&job_id, NULL) == 0) {
      printf("Got Job # %d\n", job_id);
      sleep(2);
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
  uint32_t idx;
  pthread_t tid;

  /* push dummy jobs */
  for (idx = 0; idx < 10; ++idx)
    push_job(NULL);

  printf("Show available jobs: \n");
  show_jobs();

  int ret =  pthread_create(&tid, NULL, tid_callback, NULL);
  check_status(ret == 0, "Fail to create a pthread");

  ret =  pthread_join(tid, NULL);
  check_status(ret == 0, "Fail to join a pthread");

  return 0;
}
