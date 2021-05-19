#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

void main()
{
   
    pid_t pid1,pid2,pid3;   //pid_t is a signed integer datatype which stores processes id
    pid1=fork();
    pid2=fork();
    pid3=fork();
    if(pid1==0 || pid2==0 || pid3==0){
        printf("\nInside Child Process\n Child's PID : %d \tIts Parent's PID : %d",getpid(),getppid());
    }
    else{
                 printf("Three fork function calls,Total 8 processes = 1 original process, 7 child processes \n");
                printf("\nInside Original Process\n Parent's process ID : %d\n",getpid());
     }
  
}