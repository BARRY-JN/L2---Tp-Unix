#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int indice_mot(int argc, char **argv, char *mot){
int i;
for(i=1;i<argc;i++){
        if(strcmp(argv[i],mot)==0){
                return 1;
        }
}
return 0;
}

void execut(int k, char **argv, int ind_c, int ind_s){
struct timeval temps_avant, temps_apres;
int i,error;
gettimeofday (&temps_avant, NULL);
for(i=0;i<k;i++){
        pid_t p=fork();
        if(p<0){perror("fork");exit(1);}
        if(p==0){
                execvp(argv[ind_c],argv+ind_c);
                perror("exec");
                exit(1);
        }
        if(ind_s!=0){
                wait(&error);
                printf("Code de sortie: %d\n\n",WEXITSTATUS(error));
        }else{
                wait(NULL);
        }
}
gettimeofday (&temps_apres, NULL);
printf("temps en us: %ld us\n",(temps_apres.tv_usec - temps_avant.tv_usec)/k);
}

int main(int argc, char **argv){
int ind_n, ind_s, ind_c,k;
if(argc<2){
printf("Pas assez d'arguments !\n");
exit(1);
}  
ind_n=indice_mot(argc,argv,"-n");
k=1;
if(ind_n!=0){
        ind_n++;
        k=atoi(argv[ind_n]);
        }
ind_s=indice_mot(argc,argv,"-s");
ind_c=ind_n+ind_s+1;
execut(k,argv,ind_c,ind_s);
}
