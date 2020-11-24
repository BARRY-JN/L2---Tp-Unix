#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
int ind_then,ind_else,ind_f,n,i;
n=argc;
for(i=0;i<n;i++){
if(strcmp(argv[i],"--then")==0){
	ind_then=i;
	argv[i]=NULL;
}
if(strcmp(argv[i],"--else")==0){
	ind_else=i;
	argv[i]=NULL;
}
if(strcmp(argv[i],"--fi")==0){
	ind_f=i;
	argv[i]=NULL;
}
}
pid_t p = fork();
	if (p < 0) { perror("fork"); exit (1); }
	if (p == 0) {  /* Fils */
		execvp (argv[1],argv+1);
		perror ("execup");
		exit (1);
	}
	
	wait(&i);
	n=WEXITSTATUS(i);
	printf("%d\n",n);
	if(n==0){
		p = fork();
		if (p < 0) { perror("fork"); exit (1); }
		if (p == 0) {  /* Fils */
			execvp (argv[ind_else+1],argv+(ind_else+1));
			perror ("execup");
			exit (1);
		}
		wait(&i);
		WEXITSTATUS(i);
		printf("%d\n",n);
	}else{
		p = fork();
		if (p < 0) { perror("fork"); exit (1); }
		if (p == 0) {  /* Fils */
			execvp (argv[ind_f+1],argv+ind_f+1);
			perror ("exec ls");
			exit (1);
		}
		wait(&i);
		WEXITSTATUS(i);
		printf("%d\n",n);
	}
exit (0);
}
