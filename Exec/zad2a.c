#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>



int main(int argc, char *argv[])
{
    int a;

    //printf("dane procesu macierzystego:\n");
    //getprocess();

    for(int i=0;i<3;i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
    
            case 0:
                //akcja procesu potomnego
                //printf("dane procesu potomnego:\n");
                //getprocess();
                execlp("./zad2b","zad2b",NULL);
                perror("execl error");
                break;
               default:
                // akcja dla procesu macierzystego wait
                if(wait(NULL)==-1)
                {
                perror("Wait error");
                exit(1);
                }
                break;
        }

    }
    printf("macierzysty\n");
    execlp("./zad2b","zad2b",NULL);
    return 0;
}