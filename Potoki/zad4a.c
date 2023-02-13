#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>


int main(int argc , char *argv[])
{
    int pidkons;
    int pidprod;
    int potok[2];
    int b =0;
    if(argc =! 4)
    {
        printf("Blad liczby argumentow");
        exit(1);
    }


    if(pipe(potok)==-1)
    {
        perror("Błąd potoku");
    }
    char potok1[sizeof(potok[1])];
    sprintf(potok1,"%d",potok[1] );
    char potok2[sizeof(potok[0])];
    sprintf(potok2,"%d",potok[0] );

    switch(pidprod=fork())
        {
            case -1:
                perror("fork error");
                exit(1);
    
            case 0:
                //akcja procesu potomnego producenta
                if(execlp("./zad4prod.x","zad4prod.x",argv[1],argv[3],potok1,NULL) == -1)
                {
                    perror("execpl error");
                    exit(1);
                }
                //break;
               default:

               break;
                
         //argv1 wielkosc kontener prod 2 wielkosc kontener kons
         //3 plik dla prod 4 plik dla kons        
        }
        
        switch(pidkons=fork())
        {
            case -1:
                perror("fork error");
                exit(1);
    
            case 0:
                //akcja procesu potomnego konsumenta
                if(execlp("./zad4kons.x","zad4kons.x",argv[2],argv[4],potok2,NULL) == -1)
                {
                    perror("execpl error");
                    exit(1);
                }
                
               default:
                //akcja procesu macierzystego
               break;
                

                //wait obluga wypisanie dzialania 
                printf("Uruchomienie programow prod kons\n");
        }
        for(int i =0;i<2;i++)
        {
        if(wait(&b)==-1)
        {
            printf("Wait error ");
            exit(1);
        }
        printf("Działanie programow zakonczone poprawnie\n ");
        }
        
        return 0;
}        