#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>


int main(int argc , char *argv[])
{   
    setpgid(0,0);
    int kidPid;
    int b =0;

    for(int i=0;i<3;i++)
    {
        switch(kidPid=fork())
        {
            case -1:
                perror("fork error");
                exit(1);
    
            case 0:
                //akcja procesu potomnego
                if(execlp("./zad3a.x","zad3a.x",argv[1],argv[2],NULL) == -1)
                {
                    perror("execpl error");
                    exit(1);
                }
                break;
               default:
                //
                break;
        }
    }    
       if(signal(atoi(argv[1]),SIG_IGN) == SIG_ERR)
       {
           perror("SIGINT error");
           exit(1);       
       }
       int process;
       for(int i =0;i<3;i++)
       {   
            if(wait(&b)==-1)
            {
                printf("abrakadabra");
                printf("Wait ERROR");
                exit(1);
            } 
            printf("Proces %d zakonczony\n",b);

       }
    
}