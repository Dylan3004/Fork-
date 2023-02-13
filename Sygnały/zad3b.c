#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>


int main(int argc , char *argv[])
{

    if(argc != 3)
    {
        printf("Arguments ERROR");
        exit(1);
    }
    int kidPid;
    printf("PID procesu: %d\n",getpid());
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
                //break;
               default:
                
                sleep(2);

                if(kill(kidPid,0)==-1)
                {
                    perror("dziecka nie ma ");
                    exit(1);
                }
                if(kill(kidPid,atoi(argv[1])))
                {
                    perror("Function KILL ERROR");
                    exit(1);
                }
                
                break;
        }
    return 0;
}