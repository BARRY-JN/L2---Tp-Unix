#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){
pid_t p = fork();
		if (p < 0) { perror("fork"); exit (1); }
		if (p == 0) {  /* Fils */
			execlp ("who", "who", NULL);
			perror ("exec who");
			exit (1);
		}
		int i;
		wait(&i);
		int n=WEXITSTATUS(i);
		printf("%d\n",n);
		p = fork();
		if (p < 0) { perror("fork"); exit (1); }
		if (p == 0) {  /* Fils */
			execlp ("pwd", "pwd", NULL);
			perror ("exec pwd");
			exit (1);
		}
		wait(&i);
		WEXITSTATUS(i);
		printf("%d\n",n);
		p = fork();
		if (p < 0) { perror("fork"); exit (1); }
		if (p == 0) {  /* Fils */
			execlp ("ls", "ls","-l", NULL);
			perror ("exec ls");
			exit (1);
		}
		wait(&i);
		WEXITSTATUS(i);
		printf("%d\n",n);

exit (0);
}
