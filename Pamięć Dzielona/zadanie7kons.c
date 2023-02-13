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
        int licznik ;
    } SegmentPD;




int main(int argc , char *argv[])
{

    int plik;
    int pamiec;
    SegmentPD *wpd;
    int wynik;
   
    double nap = 1.5;
    sem_t *konsument;
    sem_t *producent;
    
    plik = open(argv[4],O_WRONLY | O_CREAT | O_TRUNC ,0644 );
    if(plik == -1)
    {
        printf("blad otwarcia pliku wyjscia");
        exit(1);
    }
    int aa ;

    producent= otworz_semafor(argv[1]);
    konsument =otworz_semafor(argv[2]);
    pamiec=otworz_pamiec(argv[3]);
    printf("otworzono semafory i pamiec w programie konsumenta\n");
    wpd = (SegmentPD *) zmapuj(pamiec,sizeof(SegmentPD));
    wpd->wstaw=0;
    

    
    while(1)
    {
        upusc_semafor(konsument);
        printf("Licznik:%d\n",wpd->licznik);
        if(wpd->licznik==0)
        {
            break;
        }
        //sleep((double)(rand()%(int) (nap*50))/30);
        if((aa = write(plik,wpd->bufor[wpd->wyjmij],wpd->licznik))==-1)
        {
            perror("Blad odczytu z potoku");
            exit(1);
        }
        else{
            printf("KONSUMENT:\n");
            wartosc_semafora(producent,&wynik);
            printf("wartosc semafora producenta: %d \n",wynik);
            wartosc_semafora(konsument,&wynik);
            printf("wartosc semafora konsumenta: %d \n",wynik);
            printf("%s\n",wpd->bufor[wpd->wyjmij]);
            printf("indeks bufora %d wielkosc bufora:%d\n",wpd->wyjmij,aa);
        }
        if(wpd->licznik!=NELE)
        {
            printf("aaa");
            break;
        }

        wpd->wyjmij=(wpd->wyjmij+1)%NBUF;
        podnies_semafor(producent);
    }
        printf("Odbior pliku: Done\n");

    if(close(plik)== -1)
        {
            printf("Blad zamknieczia pliku wyjscia");
            exit(1);
        }
        zamknij_pamiec(pamiec);
        zamknij_semafor(producent);
        zamknij_semafor(konsument);
        printf("Akcja Konsumenta: Done\n");
    return 0;
}
