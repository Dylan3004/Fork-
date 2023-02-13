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


int main(int argc , char *argv[])
{
    //int plik = atoi()
    char bufor[atoi(argv[1])];
    int buforsize = atoi(argv[1]);
    int plik;
    int potok=atoi(argv[3]);
    bool loop = true;
    bool loop1 = true;
    double nap = 1.5;
    
    plik = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC ,0644 );
    if(plik == -1)
    {
        printf("blad otwarcia %s",argv[2]);
        exit(1);
    }
    int aa ;
    //printf("bbbb\n");
    while(loop)
    {
        sleep((double)(rand()%(int) (nap*50))/30);
        switch(aa = read(potok,bufor,buforsize))
        {
            case -1:
            perror("Blad odczytu z potoku");
            exit(1);
            break;
            case 0:
            //loop = false;
            break;
            default:
            ///cos 
            break;
        }
        if(bufor[aa-1]==EOF)
        {
            loop = false;
            aa-=1;
        }
        write(1,&bufor,aa);
        switch(write(plik,bufor,aa))
        {
            case -1:
            printf("Blad zapisu do pliku");
            exit(1);
            break;
            case 0:
            //loop1 = false;
            break;
            default:
            ///cos 
            break;
        }
    }
        printf("Odbior pliku: Done\n");

    if(close(plik)== -1)
        {
            printf("Blad zamknieczia pliku wyjscia");
            exit(1);
        }
        if(close(potok)==-1)
        {
            printf("Blad zamkniecia potoku");
            exit(1);
        } 
        printf("Akcja Konsumenta: Done\n");
    return 0;
}
