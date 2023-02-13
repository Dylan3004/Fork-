#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>


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
    int process_kid=0;
    int b = 3;
    int g = 0;

    printf("dane procesu macierzystego:\n");
    getprocess();

    for(int i=0;i<3;i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
    
            case 0:
                //akcja procesu potomnego
                process_kid++;
                printf("dane procesu potomnego:\n");
                printf("dziecko numer:%d\n",process_kid);
                getprocess();
                sleep(1);
                
                break;
               default:
                // akcja dla procesu macierzystego wait 
           	sleep(6);
                break;
        }
        
    }
    return 0;
}
