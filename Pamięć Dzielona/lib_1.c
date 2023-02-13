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
#include"lib_1.h"



sem_t *otworz_semafor(const char* name)
{
    sem_t *adres_semafora;
    if((adres_semafora=sem_open(name,0))==SEM_FAILED)
    {
        perror("blad w operacji otwarcia semafora");
        exit(1);
    }
    else
    {
        return adres_semafora;
    }
}
sem_t *stworz_semafor(const char* name)
{
    sem_t *adres_semafora;
    if((adres_semafora= sem_open(name,O_CREAT | O_EXCL,0664,1))== SEM_FAILED)
    {
        if((adres_semafora=otworz_semafor(name))==-1)
        {
             perror("blad w operacji tworzenia semafora final");
        exit(1);
        }
       
    }
    else
    {
        return adres_semafora;
    }
    
}
    void zamknij_semafor(sem_t *sem_t)
    {
        if(sem_close(sem_t)==-1)
        {
            perror("blad w operacji zamkniecia semafora");
            exit(1);
        }
    }
    void wartosc_semafora(sem_t* sem, int *sval)
    {
        if(sem_getvalue(sem,sval)==-1)
        {
            perror("blad w operacji uzuskiwaniq wartosci semafora");
            exit(1);
        }
    }
    void upusc_semafor(sem_t *sem)
    {
        if(sem_wait(sem)==-1)
        {
            perror("blad w operacji upuszczenia semafora");
            exit(1);
        }
    }
    void podnies_semafor(sem_t *sem)
    {
        if(sem_post(sem)==-1)
        {
            perror("blad w operacji podnoszenia semafora");
            exit(1);
        }
    }
    void usun_semafor(const char *name)
    {
        if(sem_unlink(name)==-1)
        {
            perror("blad podczas operacji usuwania semafora");
            exit(1);
        }
    }
    int otworz_pamiec(const char *name)
    {
        int final = shm_open(name, O_RDWR , 0644);
        if(final==-1)
        {
            
            perror("blad w otworzeniu pamieci dzielonej\n");
            exit(1);
            
        }
        else{
            return final;
        }
    }
        int stworz_pamiec(const char *name)
    {
        int final = shm_open(name, O_EXCL|O_CREAT | O_RDWR, 0644);
        if(final==-1)
        {
            if((final = otworz_pamiec(name))==-1)
            {
                perror("blad kompletny");
                exit(1);
            }
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
