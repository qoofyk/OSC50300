#include <unistd.h>  
#include <stdio.h>   
int main ()   
{   
    pid_t fpid;
    int count=0;  
    fpid=fork();   
    if (fpid < 0)   
        printf("error in fork!\n");   
    else if (fpid == 0) {  
        printf("i am the child process, my process id is %d\n",getpid());   
        printf("i am the child of my parent! \n");
        count++;  
    }  
    else {  
        printf("i am the parent process, my process id is %d\n",getpid());   
        printf("i am the parent of my child! \n");
	count++;  
    }  
    printf("count is %d \n",count);
    return 0;  
}
