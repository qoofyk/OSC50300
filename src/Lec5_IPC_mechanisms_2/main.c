#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFFER_SIZE  (128)

struct CommonArea {
  char   buffer[BUFFER_SIZE];
};

void                do_parent_process(struct CommonArea*);
void                do_child_process();
struct CommonArea*  create_global_common_area(size_t poolsize_per_core, int is_parent, int* shm_id);


int main(int argc, char* argv[]) {
  int                  status;
  struct CommonArea*   g_area;
  int                  shm_id; 

  g_area =  create_global_common_area(sizeof(*g_area), 1, &shm_id);

  if( fork() == 0 ) { //I'm child
    do_child_process();
  } 
  else { //I'm parent
    do_parent_process(g_area);
    wait(&status);
    if (shmdt(g_area) == -1) {
      printf("Parent: Can't detach memory segment\n");
      exit(1);
    }
    printf("Parent: detached memory segment\n");

    /* Remove the shared memory segment */
    if (shmctl(shm_id, IPC_RMID, NULL)) {
      printf("Parent: Can't remove memory segment\n");
      exit(1);
    }
    printf("Parent: removed memory segment\n");

  }

  return 0;
}


struct CommonArea* create_global_common_area(size_t size, int is_parent, int* shm_id) {
  key_t               key = 56;
  void               *shm;
  struct CommonArea  *g_area;
  int                 shm_flg = 0;

  if(is_parent) {
    shm_flg = IPC_CREAT | 0666;
  }

  if ((*shm_id = shmget(key, sizeof(*g_area), shm_flg)) < 0) {
    printf("Error: shmget() failed\n");
    exit(1);
  }

  if ((shm = shmat(*shm_id, NULL, 0)) == (void *) -1) {
    printf("Error: shmat() failed\n");
    exit(1);
  }


  g_area = (struct CommonArea*) shm; 

  return g_area;
}



void do_parent_process(struct CommonArea* g_area) {
  int                 pid;

  pid = getpid();


  sprintf(g_area->buffer, "Hello, I am the parent(PID=%d)\n", pid);

  printf("Parent writes data to shm segment!\n");
}


void do_child_process() {
  struct CommonArea  *g_area;
  int    shm_id;
  g_area = create_global_common_area(sizeof(*g_area), 0, &shm_id);
  
  sleep(1);

  printf("Child reads from shm segment: %s", g_area->buffer);
  if(shmdt(g_area) == -1) {
    printf("Child: Can't detach memory segment\n");
    exit(1);
   }
   printf("Child: detached memory segment\n");

}



int gen_rand(int n) { //return 0 : n -1
  return  ( ((double) rand()) / RAND_MAX ) * n;
}


double get_cur_time() {
  struct timeval   tv;
  struct timezone  tz;
  double cur_time;

  gettimeofday(&tv, &tz);
  cur_time = tv.tv_sec + tv.tv_usec / 1000000.0;

  return cur_time;
}

