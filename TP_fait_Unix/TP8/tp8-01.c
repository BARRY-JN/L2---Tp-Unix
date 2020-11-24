#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int cmt = 0;

int mysignal (int sig, void (*h)(int), int options)
{
	struct sigaction s;
	s.sa_handler = h;
	sigemptyset (&s.sa_mask);
	s.sa_flags = options;
	int r = sigaction (sig, &s, NULL);
	if (r < 0) perror (__func__);
	return r;
}

void capter (int sig)
{
	mysignal (SIGUSR1, capter, SA_RESTART);
	printf ("Recu signal %d n° %d\n", sig,cmt);
	cmt++;
}

int main(int argc, char *argv[]){
	int p;
	int pere=getpid();
	int i,n;
	
	if(argc<2){
		printf("Usage: mettre un n please\n");
		exit(1);
	}
	n=atoi(argv[1]);
	mysignal (SIGUSR1, capter, SA_RESTART);

	p = fork();
	if(p<0){
		perror("fork");
		exit(1);
	}
	if(p==0){//fils
		for(i=0;i<n;i++)
			kill(pere,SIGUSR1);
	
		exit(0);
	}
	//pere
	wait(NULL);
	printf("Signaux recus: %d\n",cmt);
	return 0;
}
