#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/stat.h>

#include "psem.h"

// Get semaphore
int psem_get(key_t key, int *sema_id)
{
  // Let's reterieve existing semaphore
  int id = semget(key, 1, 0);
  if (id == -1) {
    return errno;
  }

  *sema_id = id;
  return 0;
}

// Create semaphore
int psem_open(key_t key, int *sema_id)
{
  int ret;

  // Create semaphore
  int id = semget(key, 1, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
  if (id == -1) {
    return errno;
  }

  ret =  semctl(id, 0, SETVAL, 1);
  if (ret == -1) {
    (void)psem_destroy(id);
    return errno;
  }

  *sema_id = id;
  return 0;
}

// Destory semaphore
int psem_destroy(int sema_id)
{
  int ret =  semctl(sema_id, 0, IPC_RMID);
  if (ret == -1) {
    return errno;
  }

  return 0;
}

// Handy function for wait
static int util_wait(int sema_id, short int flags)
{
  struct sembuf buf;
  buf.sem_flg = flags;
  buf.sem_num = 0;
  buf.sem_op = -1;    /* Decrement it */
  return semop(sema_id, &buf, 1);
}

// Wait on semaphore (Blocking)
int psem_wait(int sema_id) {
  int ret =  util_wait(sema_id, SEM_UNDO);
  if (ret == -1)
    return errno;
  return 0;
}

// Wait on semaphore (Non-Blocking)
int psem_trywait(int sema_id)
{
  int ret =  util_wait(sema_id, SEM_UNDO | IPC_NOWAIT);
  if (ret == -1)
    return errno;
  return 0;
}

// Post a semaphore
int psem_post(int sema_id)
{
  struct sembuf buf;
  buf.sem_flg = SEM_UNDO; /* This flag allows to reset semaphore in case process is terminates by anyway */
  buf.sem_num = 0;
  buf.sem_op = 1;     /* Increment it */
  int ret =  semop(sema_id, &buf, 1);
  if (ret == -1) {
    return errno;
  }

  return 0;
}
