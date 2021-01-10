#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int seconds;

void alarm_handler(int dummy) {
  ++seconds;

  printf("%d seconds has passed\n", seconds);

  //exercise 1: remove this alarm below.
  alarm(1);

  //exercise 2:
  //while(1);
}

void ctl_c_handler(int dummy) {
  printf("Hello, you typed CTL-C\n");
}

int main(int argc, char* argv[]) {
  int i;

  signal(SIGALRM, alarm_handler); //register my own signal handler.
  //signal(SIGINT, ctl_c_handler); // related to exercise2:
  alarm(1);  

  for(i = 0; i < 9000000000; i++);

  return 0;
}
