#include <stdio.h>
#include <signal.h>

void ctrl_c_handler(int tmp) {
  printf("You typed CTL-C, but I don't want to die!\n");
  // while(1); //Q: what would happen?
}

int main(int argc, char* argv[]) {
  long i;

  signal(SIGINT, ctrl_c_handler);
  for(i = 0; i < 5000000000; i++);  

  return 0;
}
