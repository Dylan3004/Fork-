#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
//extern const char* const sys_siglist[];
void user_function()
{
    
     printf("Wypisanie PIDu %d",getpid());
}



int main(int argc , char*argv[])
{
    if(argc != 3)
    {
        printf("Argument error");
        exit(1);
    }
    //printf("PID process %d\n",getpid());

    if(strcmp(argv[2],"ignore")==0)
    {
        if(signal(atoi(argv[1]),SIG_IGN)==SIG_ERR)
        {
            perror("Problem z SIG_INT");
            exit(1);
        }
    }
    else if(strcmp(argv[2],"default")==0)
    {
        if(signal(atoi(argv[1]),SIG_DFL)== SIG_ERR)
        {
            perror("Problem z SIG_INT");
            exit(1);
        }
    }
    else if(strcmp(argv[2],"other")==0)
    {
        if(signal(atoi(argv[1]),user_function)==SIG_ERR)
        {
            perror("Problem z SIG_INT");
            exit(1);
        }
    }
    else
    {
        printf("Zla komenda %s\n",argv[2]);
    }
    pause();
    //test printf("aaaa");

    return 0;
}