#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

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
    
    getprocess();
    
    return 0;
}                        