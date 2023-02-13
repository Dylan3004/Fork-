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
#include"biblioteka.h"

sem_t *stworz_semafor(const char* name)
{
    sem_t *adres_semafora;
    if((adres_semafora= sem_open(name,O_CREAT | O_EXCL,0664,1))== SEM_FAILED)
    {
        perror("blad w operacji tworzenia semafora");
        exit(1);
    }
    else
    {
        return adres_semafora;
    }
    
}
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
