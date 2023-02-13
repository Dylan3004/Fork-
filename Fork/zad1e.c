#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
//#include"zad1a.c"

void getprocess()
{
    int uid,gid,pid,ppid,pgid;
    uid = getuid();
    gid = getgid();
    pid = getpid();
    ppid = getppid();
    pgid = getpgid(pid);
 
    printf("Process UID number:%d\n",uid);
    printf("Process GID number:%d\n",gid);
    printf("Process PID number:%d\n",pid);
    printf("Process PPID number:%d\n",ppid);
    printf("Process PGID number:%d\n",pgid);
}
int main()
{
    int process_kid=1;
    int b = 3;
    int g = 0;
    

    printf("dane procesu macierzystego:\n");
    getprocess();

    for(int i=0;i<2;i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
    
            case 0:
                //akcja procesu potomnego
                printf("dane procesu potomnego:\n");
                printf("dziecko numer:%d\n",process_kid);
                getprocess();
                //sleep(1);
                process_kid++;
                if(setpgid(0,0)==-1)
                {
                    perror("PGID error");
                }
                int pid1 = getpid();
                //printf("\n");
                printf("New PGID:%d\n",getpgid(pid1));
                break;
               default:
                // akcja dla procesu macierzystego wait 
                wait(&b);
                break;
        }
        
    }
    return 0;
}