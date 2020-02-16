#ifndef PSEM_H
#define PSEM_H

#include <sys/sem.h>

int psem_get(key_t key, int *sema_id);
int psem_open(key_t key, int *sema_id);
int psem_destroy(int sema_id);
int psem_wait(int sema_id);
int psem_trywait(int sema_id);
int psem_post(int sema_id);

#endif /* ! PSEM_H */
