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

int potok;
void fileclosing()
{
    if(close(potok)==-1)
    {
        perror("file closing error");
    }
}

int main(int argc , char *argv[])
{
    atexit(fileclosing);
    bool loop = true;
    bool loop1 = true;
    int plik;
    int buforsize = atoi(argv[1]);
    unsigned char bufor [atoi(argv[1])];
    //int potok=atoi(argv[3]);
    printf("\n %s \n",argv[2]);
    int potok = open(argv[3],O_WRONLY);
    plik = open(argv[2],O_RDONLY );
    double nap = 1.5;
    srand(time(NULL));
    if(plik== -1)
    {
        printf("blad otwarcia %s",argv[2]);
        exit(1);
    }
    //printf("\n%d\n",plik);
    int aa;
    while(loop)
    {
        sleep((double)(rand()%(int) (nap*50))/30);
        switch(aa = read(plik,&bufor,buforsize))
        {
            case -1:
            printf("%s",bufor);
            perror(" Blad odczytu z pliku");
            exit(1);
            break;
            case 0:
            loop = false;
            break;
            default:
            ///cos 
            break;
        }
        //printf("\n%d\n",potok);
        switch(write(potok,&bufor,aa))
        {
            case -1:
            perror("Blad zapisu z potoku");
            exit(1);
            break;
            case 0:
            //loop1 = false;
            break;
            default:
            ///cos 
            break;
        }
        write(1,&bufor,aa);
    }   
        printf("Przesyl pliku: Done\n");
        bufor[0]=EOF;
        write(potok,&bufor,1);

        if(close(plik)== -1)
        {
            printf("Blad zamknieczia pliku wyjscia");
            exit(1);
        }
        printf("Akcja Producenta: Done\n");

     
        return 0;
        
    



}