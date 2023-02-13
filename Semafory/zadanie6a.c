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

bool start_ok;
char nazwa_semafora[20];


 void wyjscie ()
 {
     if(start_ok)
     {
        usun_semafor (nazwa_semafora);
     }
 }
 void usuwanie_sygnal(int signal)
 {
     if(start_ok)
     {
         usun_semafor (nazwa_semafora);
         printf("Sygnal przerwania semafora");
     }
 }


int main(int argc, char *argv[])
{
    if(argc !=7)
    {
        perror("blad niepoprawna liczba argumentow");
        exit(1);

    }
    if(atexit(wyjscie)!=0)
    {
        perror("blad w wychodzeniu funkcja atexit\n");
        exit(1);
    }
    if(signal(SIGINT,usuwanie_sygnal) == SIG_ERR)
    {
        perror("blad w przerwaniu funkcji ctrl c\n");
        exit(1);
    }

    int b;
    int ilosc_inkrementacji = atoi(argv[2]);
    int plik;
    char bufor[20];
    int odczyt;

    strcpy(nazwa_semafora,argv[5]);
    if(atoi(argv[6])== 0)
    {
        start_ok =false ;
    }
    else
    {
        start_ok=true;
    }
    if( (plik =open(argv[4],O_WRONLY | O_CREAT | O_TRUNC,0644))==-1)
    {
        perror("blad otwarcia pliku do pisania\n");
        exit(1);
    }
    if(write(plik,"0",2)==-1)
    {
        perror("blad w zapisie do pliku\n");
        exit(1);
    }
    if(close(plik)==-1)
    {
        perror("blad w zamknieciu pliku\n");
        exit(1);
    }
    if(start_ok)
    {
        sem_t *semafor = stworz_semafor(nazwa_semafora);
        int wartosc_semafor;
        wartosc_semafora(semafor,&wartosc_semafor);
        printf("utworzono semafor o wartosci %d \n",wartosc_semafor);
    }
    for(int i =0; i< ilosc_inkrementacji;i++)
    {
        switch (fork())
        {
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:
            //potomny
            
            execl("./zadanie6.x","zadanie6.x",argv[3],argv[4],argv[5],argv[6],NULL);
            perror("execl error");
            exit(1);
        
        default:
            break;
        }
    }
    //czekanie na procesy potomne 
    for(int i =0;i<ilosc_inkrementacji;i++)
    {
        if(wait(&b)==-1)
        {
            perror("wait error\n");
            exit(1);

        }
    }
    if((plik=open(argv[4],O_RDONLY,0644))==-1)
    {
        perror("blad otwarcia pliku\n");
        exit(1);
    }
    odczyt = read(plik,&bufor,10);
    switch(odczyt)
    {
    case -1:
        perror("blad w odczycie pliku\n");
        exit(1);
        break;
    case 0:
        printf("Blad znikna (turudutudu - tu - turudutudu - tu)\n");
        exit(1);
    default:
       
        if(atoi(bufor) == (atoi(argv[2]) * atoi(argv[3])))
        {
            printf("Hurra otrzymano wynik to %d i jest poprawny\n", atoi(bufor));
        }
        else
        {
            int poprawny = (atoi(argv[2]) * atoi(argv[3]));
            printf("Cos poszlo nie tak mialo byc %d a otrzymano %d\n",poprawny,atoi(bufor));
        
        }
    }

    if(close(plik)==-1)
    {
        perror("blad koncowego zamkniecia pliku\n");
        exit(1);
    }

    return 0;
}