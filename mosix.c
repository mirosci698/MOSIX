#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#define DLUGOSC 5
 
int silnia(int liczba)
{
        if (liczba < 2)
        {
                return 1;
        } else 
        {
                return liczba * silnia(liczba - 1);
        }
}
 
int main(int argc, char** argv)
{
        srand(time(NULL));
        
        int n = atoi(argv[1]);
        int *liczby;
        liczby = (int*)malloc(DLUGOSC);
        int i;
        for (i = 0; i < DLUGOSC; i++)
        {
                liczby[i] = rand() % 10;
        }
        printf("Wylosowane n");
        for (i = 0; i < DLUGOSC; i++)
        {
                printf("%d n", liczby[i]);
        }
        printf("Obliczenia n");
        int potok1[2];
        int potok2[2];
        pipe(potok1);
        pipe(potok2);
        int tmp;
        int arg;
        int suma = 0;
        for (i = 0; i < DLUGOSC; i++)
        {
                write(potok1[1], &liczby[i], sizeof(int));
        }
        for (i = 0; i < n; i++)
        {
                if (fork() == 0)
                {
                        while(1)
                        {
                                read(potok1[0], &arg, sizeof(int));
                                tmp = silnia(arg); 
                                write(potok2[1], &tmp, sizeof(int));
                        }
                }
        }
        for (i = 0; i < DLUGOSC; i++)
        {
                read(potok2[0], &tmp, sizeof(int));
                suma += tmp;
        }
        printf("%d n", suma);
        kill(0, SIGTERM);
        return 0;
} 