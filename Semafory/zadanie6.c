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



int main (int argc,char *argv[])
{
    char bufor [20];
    bool start_ok;
    sem_t *semafor;
    int wartosc;
    int plik;
    int odczyt;
    int liczba=0;
    //printf("aaa");

    if(argc != 5)
    {
        perror("program zainicjalizowany z niepoprawna liczba argumentow\n");
        exit(1);
    }
    


    if( atoi (argv[4]) == 0)
    {
        start_ok = false;
    }
    else
    {
        start_ok = true;
        //perror("zla liczba podanych argumentow");
        //exit(1);
    }
    if(start_ok)
    {
        semafor = otworz_semafor(argv[3]);
    }
    for(int i=0;i<atoi(argv[1]);i++)
    {
        srand(time(NULL));
        // losowy czas czekania
        sleep((double)(rand()% (int)(12*30))/60);

        if(start_ok)
        {
            wartosc_semafora(semafor,&wartosc);
            printf("Wartosc semafora = %d , PID semafora=%d przed sekcja krytyczna\n",wartosc,getpid());
            upusc_semafor(semafor);

        }
        if(( plik = open(argv[2],O_RDONLY,0644)) == -1)
        {
            perror("blad otwarcia pliku od czytania\n");
            exit(1);
        }
        if((odczyt = read(plik,&bufor,10))==-1)
        {
            perror("blad czytania pliku\n");
            exit(1);
        }
        else
        {
            
            wartosc_semafora(semafor,&wartosc);
            printf("Wartosc semafora = %d , PID semafora=%d odczytany numer=%s, iteracja sekcji krytycznej = %d\n",wartosc,getpid(),bufor,i);
        }

        if(close(plik)==-1)
        {
            perror("blad zamkniecia pliku\n");
            exit(1);
        }
        
        // tworzenie nowej liczby do zapisu w pliku
        liczba = atoi(bufor)+1;
        sprintf(bufor,"%d",liczba); 
        printf("Liczba = %d\n",liczba);

        // losowy czas czekania
        sleep((double)(rand()% (int)(12*30))/60);
        // operacja zapisu
        if((plik=open(argv[2],O_CREAT | O_WRONLY | O_TRUNC,0664))==-1)
        {
            perror("blad w otwrciu pliku do pisania\n");
            exit(1);
        }
        if(write(plik,&bufor,strlen(bufor))==-1)
        {
            perror("blad w pisaniu w pliku\n");
            exit(1);
        }
         if(close(plik)==-1)
        {
            perror("blad zamkniecia pliku\n");
            exit(1);
        }
        if(start_ok)
        {
            podnies_semafor(semafor);
            wartosc_semafora(semafor,&wartosc);
            printf("Wartosc semafora = %d , PID semafora=%d po sekcji krytycznej \n",wartosc,getpid());
        }
        printf("=========================================\n");
       
        
    }
    
    
     if(start_ok)
        {
            zamknij_semafor(semafor);
        }
        
    return 0;
}