#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
int i,n;
	n=atoi(argv[1]);
	printf ("Père : %d \n", (int) getpid());
	for(i=1;i<=n;i++)
	{
		pid_t p = fork();
		if (p < 0) { perror("fork"); exit (1); }
		if (p == 0) {  /* Fils */
			printf ("fils %d : %d \n",i ,(int) getpid());
			exit (0);
			}
	} /* Fin fils */
	/* Suite du p`ere */
	
	exit (0);
}
