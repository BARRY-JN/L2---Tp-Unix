#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
int i,j,f,pf;
	f=atoi(argv[1]);
	pf=atoi(argv[2]);
	printf ("%d %d \n", f, pf);
	printf ("Père : %d \n", (int) getpid());
	for(i=1;i<=f;i++)
	{
		pid_t p1 = fork();
		if (p1 < 0) { perror("fork"); exit (1); }
		if (p1 == 0) 
		{  
			printf ("fils %d : %d \n",i ,(int) getpid());
			for(j=1;j<=pf;j++)
			{
				pid_t p2 = fork();
				if (p2 < 0) { perror("fork"); exit (1); }
				if (p2 == 0) 
				{  
					printf ("         petit-fils %d de %d : %d      père : %d \n",j,i,(int) getpid(), (int) getppid());
					exit(0);
				}
			
			}
			exit(0);
		}
	}
	exit (0);
}
