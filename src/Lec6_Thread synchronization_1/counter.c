#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct gv_t {
  int counter;
  int num_iterations;
}* GV;

typedef struct lv_t {
  int tid;
  GV  gv;
}* LV;

void* do_thread(void* v) {
  GV  gv;
  LV  lv;
  int tid;
  int niter;
  int i;

  lv = (LV) v;
  gv = lv->gv;
  tid     = lv->tid;
  niter   = gv->num_iterations;

  printf("Thread %d starts running...\n", tid);

  if(tid == 0) {
    for(i = 0; i < niter; ++i) gv->counter++;
  } else { 
    for(i = 0; i < niter; ++i) gv->counter--;
  }

  return NULL;
}

int main(int argc, char* argv[]) {
  int             i, n, niter;
  LV              lvs;
  GV              gv;
  pthread_t       *thrds;
  pthread_attr_t  *attrs;
  void            *retval;

  if(argc != 2) {
    fprintf(stderr, "Usage: %s num_iterations\n", argv[0]); //try num_iterations >= 100,000
    exit(1);
  }

  n     = 2;
  niter = atoi(argv[1]);
 
  gv    = (GV) malloc(sizeof(*gv));
  gv->counter = 0;
  gv->num_iterations = niter;
  lvs   = (LV) malloc(sizeof(*lvs)*n);
  thrds = (pthread_t*) malloc(sizeof(pthread_t)*n);
  attrs = (pthread_attr_t*) malloc(sizeof(pthread_attr_t)*n);

  /* Create threads */
  for(i = 0; i < n; i++) {
    lvs[i].tid = i;
    lvs[i].gv   = gv;
    if(pthread_attr_init(attrs+i)) perror("attr_init()");
    if(pthread_attr_setscope(attrs+i, PTHREAD_SCOPE_SYSTEM)) perror("attr_setscope()");
    if(pthread_create(thrds+i, attrs+i, do_thread, lvs+i)) {
      perror("pthread_create()");
      exit(1);
    }
  }

  /* Join threads */
  for(i = 0; i < n; i++) {
    pthread_join(thrds[i], &retval);
    printf("Thread %d is finished\n", i);
  }

  printf("Eventually, Counter = %d\n", gv->counter);
  
  free(gv);
  free(lvs);
  free(attrs);
  free(thrds);

  return 0;
}
