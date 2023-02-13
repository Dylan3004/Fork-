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
#include<sys/mman.h>
#include<semaphore.h>
#include"lib_1.h"
#define NELE 20
#define NBUF 5
typedef struct 
    {
        char bufor [NBUF] [NELE] ;
        int wstaw ;
        int wyjmij ;
        int licznik;
    } SegmentPD;




int main(int argc , char *argv[])
{
    //printf("aaa");
    bool loop = true;
    int plik;
    sem_t *producent;
    sem_t *konsument;
    int pamiec;
    SegmentPD *wpd;
    int wynik;

    
    plik = open(argv[4],O_RDONLY ,0644);
     if(plik== -1)
    {
        printf("blad otwarcia pliku");
        exit(1);
    }
    double nap = 1.5;
    srand(time(NULL));

    producent= otworz_semafor(argv[1]);
    konsument= otworz_semafor(argv[2]);
    pamiec=otworz_pamiec(argv[3]);

    printf("otwarto semafory oraz pamiec dzielona w pliku producenta\n");

    wpd = (SegmentPD *) zmapuj(pamiec,sizeof(SegmentPD));
    wpd->wstaw = 0;
   
   
    int aa;
    
    while(loop)
    {
        //sleep((double)(rand()%(int) (nap*50))/30);
        upusc_semafor(producent);
        aa = read(plik,wpd->bufor[wpd->wstaw],NELE);
        if(aa==-1)
        {
            perror(" Blad odczytu z pliku");
            exit(1);
        }
        if(aa==NELE)
        {
            printf("PRODUCENT:\n");
            wartosc_semafora(producent,&wynik);
            printf("wartosc semafora producenta: %d\n",wynik);
            wartosc_semafora(konsument,&wynik);
            printf("wartosc semafora konsumenta: %d\n",wynik);
            printf("%s\n",wpd->bufor[wpd->wstaw]);
            printf("indeks bufora %d wielkosc bufora:%d\n",wpd->wstaw,aa); 
        }
        if(aa!=NELE)
        {
           
            printf("PRODUCENT:\n");
            wartosc_semafora(producent,&wynik);
            printf("wartosc semafora producenta: %d\n",wynik);
            wartosc_semafora(konsument,&wynik);
            printf("wartosc semafora konsumenta: %d\n",wynik);
            printf("%s\n",wpd->bufor[wpd->wstaw]);
            printf("indeks bufora %d wielkosc bufora:%d\n",wpd->wstaw,aa);
           break;
        }
        wpd->licznik=aa;
        wpd->wstaw=(wpd->wstaw+1) %NBUF;
        podnies_semafor(konsument);
    }   
        printf("Przesyl pliku: Done\n");
        //bufor[0]=EOF;
        //write(plik,,1);

        if(close(plik)== -1)
        {
            printf("Blad zamknieczia pliku wyjscia");
            exit(1);
        }

        zamknij_pamiec(pamiec);
        zamknij_semafor(producent);
        zamknij_semafor(konsument);
        printf("Akcja Producenta: Done\n");
     
        return 0;
        
    



}