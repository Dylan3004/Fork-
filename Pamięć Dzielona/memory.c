#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdbool.h>
#include<semaphore.h>
#include<sys/mman.h>
#include"memory.h"

    int stworz_pamiec(const char *name)
    {
        int final = shm_open(name, O_EXCL|O_CREAT | O_RDWR, 0644);
        if(final==-1)
        {
            perror("blad w tworzeniu pamieci dzielonej\n");
            exit(1);
        }
        else{
            return final;
        }
    }
    int otworz_pamiec(const char *name)
    {
        int final = shm_open(name, O_EXCL|O_CREAT | O_RDWR, 0644);
        if(final==-1)
        {
            perror("blad w tworzeniu pamieci dzielonej\n");
            exit(1);
        }
        else{
            return final;
        }
    }
    int ustaw_dlogosc(int fd , off_t length)
    {
        int final = ftruncate( fd , length);
        if(final==-1)
        {
            perror("blad w ustawianiu dlugosci pamieci dzielonej\n");
            exit(1);
        }
        else
        {
            return final;
        }
    }
    int zamknij_pamiec(int fd)
    {
        int final = close(fd);
        if(final==-1)
        {
            perror("blad w zamykaniu pamieci\n");
            exit(1);
        }
        else
        {
            return final;
        }
    }
    int usun_pamiec(const char *name)
    {
        int final=shm_unlink(name);
        if(final == -1)
        {
            perror("blad w usuwaniu pamieci dzielonej\n");
            exit(1);
        }
        else
        {
            return final;
        }
        
    }
    void *zmapuj (int desc, size_t a)
    {
        void*final;
        if((final = mmap(NULL,a, PROT_READ | PROT_WRITE,MAP_SHARED,desc,0))==-1)
        {
            perror("blad w funkcji mmap");
            exit(1);
        }
        return final;
    }
