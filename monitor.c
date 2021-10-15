#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>
void printProgArgv(int count, char* argv[]);

int main(int argc, char* argv[]){
	if (argc>1){
		printf("There are %d command argument for the monitor\n",argc);
		char* progArgv[argc-1];// this array of string will be passed to the prog to be exec
		for (int i=0;i<argc-1;i++){//update the entity of progArgv by the 2nd element to the last element of argv
			printf("i=%d\n",i);
			progArgv[i]=argv[i+1];
			
		}
		progArgv[argc-1]=NULL;
		printProgArgv(argc-1,progArgv);//debug 

		int pid=fork();
		if(pid<0){
			printf("Fork() failed\n");
			exit(-1);
		}
		else if(pid==0){
			printf("child process created\n");
			//printf("%s\n",argv[2]);
			execvp(argv[1], progArgv); //   argv== {"./monitor","./hello",NULL}
			printf("execvp() Failed"); 
			exit(-1);
		}
		else 
		{
		// Parent Process
			wait(NULL);
			printf("Parent Process.\n"); 
			printf("\n");
		}
	}
	else{
		printf("No prog to be executed\n");
	}
	return 0;
}
void printProgArgv(int count, char* argv[]){
	printf("printing entities of progArgv\n");
	for(int i=0;i<count;i++){
		printf("%s ",argv[i]);
	}
	printf("\n");
}