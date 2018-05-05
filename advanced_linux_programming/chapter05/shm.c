// Listing 5.1 (shm.c) Exercise Shared Memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define check_status(expr, msg)                                         \
  if (!(expr)) {                                                        \
    fprintf(stderr, "%s\n", msg);                                       \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));    \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FILE__);  \
    exit(1);                                                            \
  }

//
// App entry point
//
int main()
{
  size_t size = 1024 * 10;

  /* Allocate a memory segement */
  int shm_id = shmget(IPC_PRIVATE, size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
  check_status(shm_id > 0, "Fail to allocate SHM");

  /* Attach memory */
  char *memory = (char *)shmat(shm_id, 0, 0);

  struct shmid_ds shm_buffer;
  int ret = shmctl(shm_id, IPC_STAT, &shm_buffer);
  check_status(ret >= 0, "Fail to get info SHM");

  printf("User asked size: %ld\n", size);
  printf("Allocated size:  %ld\n", shm_buffer.shm_segsz);

  /* Let's write data */
  size_t idx = 0, real_size = shm_buffer.shm_segsz;
  for (idx = 0; idx < real_size; ++idx) {
    memory[idx] = 'A';
  }

  /* Let's read back our data */
  for (idx = 0; idx < real_size; ++idx) {
    printf("%c", memory[idx]);
    if (idx % 24 == 0) {
      printf("\n");
    }
  }
  printf("\n");

  /* Deattach the memory */
  ret =  shmdt(memory);
  check_status(ret >= 0, "Fail to de-attach SHM");

  /* Deallocate the memory */
  ret =  shmctl(shm_id, IPC_RMID, 0);
  check_status(ret >= 0, "Fail to de-allocate SHM");

  return 0;
}
