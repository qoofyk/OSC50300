#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


long i;

void ctrl_c_handler(int tmp) {
  printf("You typed CTL-C, i = %ld\n", i);

}

void ctrl_slash_handler(int tmp) {
  printf("You typed CTL-\\, i = %ld\n", i);

}


int main(int argc, char* argv[]) {
  signal(SIGINT,  ctrl_c_handler);
  signal(SIGQUIT, ctrl_slash_handler);

  for(i = 0; i < 10000000000; i++);  

  exit(0);
}
