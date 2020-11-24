#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void capter_alarme ()
{
        printf ("No, you stay dead !\n");
        exit(0);
}

void capter_INT ()
{
        printf ("Staying alive !\n");
        signal (SIGALRM,capter_alarme);
        alarm(5);
}

int main ()
{ 
        while (1) {
                signal (SIGINT,capter_INT);
                sleep (1);
                printf ("Ah !\n");
        }
}
