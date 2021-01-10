#include <rpc/rpc.h>
#include "datestub.h"

int main(int argc, char* argv[]) {
  CLIENT *cl_handle;
  char   **reply;

  if(argc != 2) {
    fprintf(stderr, "Usage: %s server\n", argv[0]);
    exit(1);
  }

  /* create a client handle */
  if( (cl_handle = clnt_create(argv[1], MY_PROG, MY_VERS, "udp")) == NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  /* make a RPC */
  if( (reply = get_date_1(NULL, cl_handle)) == NULL ) {
    clnt_perror(cl_handle, argv[1]);
    exit(1);
  }

  printf("date on host %s = %s\n", argv[1], *reply);
  
  clnt_destroy(cl_handle);
  return 0;
}
