#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int fifoid=-1;
char *pointer;

//void pipeclosing ()
//{
//    printf("%s",*pointer);
    /*if(access(*pointer,F_OK)==-1)
    {
        if(remove(*pointer)==-1)
        {
            perror("Removing file error");
        }
    }*/
//}
    


int main(int argc , char *argv[])
{
    pointer=&argv[5];   
    int funcion;
    int pidkons;
    int pidprod;
    int b =0;
    if(argc =! 5)
    {
        printf("Blad liczby argumentow");
        exit(1);
    }
    

if(access(argv[5],F_OK)!=0)
{
    if(mkfifo(argv[5],0644)==-1)
    {
        perror("Make fifo error");
        exit(1);
    }
    
}
    //atexit(pipeclosing);

    //char potok1[sizeof(potok[1])];
    //char potok2[sizeof(potok[0])];

    switch(pidprod=fork())
        {
            case -1:
                perror("fork error");
                exit(1);
    
            case 0:
                //akcja procesu potomnego producenta
                if(execlp("./zad5aprod.x","zad5aprod.x",argv[1],argv[3],argv[5],NULL) == -1)
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
                if(execlp("./zad5akons.x","zad5akons.x",argv[2],argv[4],argv[5],NULL) == -1)
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