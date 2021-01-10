#include <stdio.h>
#include <time.h>
#include <rpc/rpc.h>
#include "datestub.h"



char**  get_date_1_svc(void * dummy1, struct svc_req * dummy2) {
  static char buffer[256];
  time_t      raw_tm;
  struct tm   *tm_info;  
  static char* ret;

  time(&raw_tm);
  tm_info = localtime(&raw_tm);

  strftime(buffer, sizeof(buffer), "It is %c", tm_info);

  ret = buffer;
  return &ret;
}
