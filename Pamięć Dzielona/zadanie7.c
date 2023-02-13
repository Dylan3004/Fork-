#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<sys/mman.h>
#include"lib_1.h"

#define NELE 20
#define NBUF 5



// instrukcja do argumentow arg1=nazwa semafora producenta (/producent) arg2= nazwa semafora konsumenta (/konsument) arg3= nazwa pamieci dzielonej (/pamiec) 
// arg4=plik wejscia arg5=plik wyjscia 

void wyjscie(void)
{  
    usun_semafor("/producent");
    usun_semafor("/konsument"); 
    usun_pamiec("/pamiec");

}
 void signal_wyjscia(int signal)
 {
     printf("wyjscie za pomoca przerwania\n");
     exit(1);
 }
    typedef struct 
    {
        char bufor [NBUF] [NELE] ;
        int wstaw ;
        int wyjmij ;
        int licznik ;
    } SegmentPD;

int main(int argc , char *argv[])
{
   //if(argc != 5)
    //{
    //    perror("zla liczba argumentow");
    //    exit(1);
    //}
    int *wartosc1;
    int *wartosc2;
    int pamiec_dzielona;
    sem_t *semafor;
    int b =0;
    int i;

    if(atexit(wyjscie) != 0)
    {
        perror("atexit error");
        exit(1);
    }
    if( signal(SIGINT,signal_wyjscia)== SIG_ERR)
    {
        perror("signal error");
        exit(1);
    }
    semafor = stworz_semafor(argv[1]);
    //podnies_semafor(semafor);
    
    wartosc_semafora(semafor,&wartosc1);
    printf("utworzono semafor producent : %s o wartosci %d  \n",argv[1],wartosc1);
    semafor = stworz_semafor(argv[2]); 
    upusc_semafor(semafor);
    wartosc_semafora(semafor,&wartosc2);
    printf("utworzono semafor producent : %s o wartosci %d  \n",argv[2],wartosc2);

    pamiec_dzielona = stworz_pamiec("/pamiec");
    ustaw_dlogosc(pamiec_dzielona,sizeof(SegmentPD));
    printf("utworzono pamiec dzielona\n");
    
    

    switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
    
            case 0:
                //akcja procesu potomnego konsumenta
                if(execlp("./zadanie7kons.x","zadanie7kons.x",argv[1],argv[2],argv[3],argv[5],NULL) == -1)
                {
                    perror("execpl error");
                    exit(1);
                }
                
               default:
                //akcja procesu macierzystego
               break;
                

                //wait obluga wypisanie dzialania 
                
        }

    switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
    
            case 0:
                //akcja procesu potomnego producenta
                if(execlp("./zadanie7prod.x","zadanie7prod.x",argv[1],argv[2],argv[3],argv[4],NULL) == -1)
                {
                    perror("execpl error");
                    exit(1);
                }
                //break;
               default:

               break;
                  
        }
        
        
        printf("Uruchomienie programow prod kons\n");
        for( i =0;i<2;i++)
        {
        if(i==1)
        {
            abort();
        }
        if(wait(&b)==-1)
        {
            printf("Wait error ");
            exit(1);
        }
        }
        printf("Działanie programow zakonczone poprawnie\n ");
        zamknij_pamiec(pamiec_dzielona);
        printf("Poprawne zakonczenie dzialania programu macierzystego\n");
        abort();
        
        return 0;
}        