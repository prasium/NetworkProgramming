#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<setjmp.h>

#define MAX 1024
jmp_buf env;

void timeout();

int main(int argc, char *argv[])
{
    int n;
    char buff[MAX];
    
    if(argc<2)
    {
        printf(" Usage : [num-secs] ");
        exit(EXIT_FAILURE);
    }

    unsigned int sec= atoi(argv[1]);

    if(signal(SIGALRM,timeout)==SIG_ERR)
    {
        perror("Signal alarm error");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
    if(setjmp(env)!=0)
    {
        printf("Read Timeout, exiting\n");
        exit(EXIT_FAILURE);
    }
    alarm(sec);
    n=read(STDIN_FILENO, buff,MAX);
    buff[n]='\0';
    if(n<0)
    {
        perror("Read Error");
    }
    else{
        printf("Read Successful (%d) bytes read: %s",n,buff);
    }
    //Ensure timer is turned off

    alarm(0);
    }
    return 0;

}

void timeout(void)
{
    printf("Inside timeout handler\n");
    longjmp(env,1);
}