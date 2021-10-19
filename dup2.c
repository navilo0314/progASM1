#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
int main(int argc, char*argv[]){
	int pfd1[2];
	int pfd2[2];
	pipe(pfd1);
	pipe(pfd2);
	char* progArgv[argc-1];// this array of string will be passed to the prog to be exec
	if (argc>1){//if there is a program to be executed
		printf("There are %d command argument for the monitor\n",argc);
		for (int i=0;i<argc-1;i++){//update the entity of progArgv by the 2nd element to the last element of argv
			printf("i=%d\n",i);
			progArgv[i]=argv[i+1];
			progArgv[i]=argv[i+1];
		}
		progArgv[argc-1]=NULL;

	if(fork()==0){//parent creates the 1st child this child can also access pdf1 
		close(pfd2[0]);
		close(pfd2[1]);
		close(pfd1[0]);
		dup2(pfd1[1],1);//set pipe1 write end to stdout (maybe the 1 indicate the stdout)
		//the stdout will get the data of fd1[]
		if(execvp(progArgv[0],progArgv)==-1){
			printf("exevp: error \n");
			exit(-1);
		}
	}
	if(fork()==0){//parent create the 2nd child this child can access to read end of pfd1 and write end of pdf2
		close(pfd1[1]);//close write end of pdf1 
		close(pfd2[0]);
		dup2(pfd1[0],0);// 2nd process's stdin = read end of fd1
		dup2(pfd2[1],1);//2nd process's stdout= write end of fd2 or the write end of fd2 will copy data to the stdout 
		if(execvp(progArgv[2],progArgv)==-1){
			printf("exevp: error \n");
			exit(-1);
		}
	}
	if(fork()==0){
	//parent create the 3rd child process this child process can only access to the read end of fd2 i.e fd[0]
		close(pfd2[1]);
		close(pfd1[0]);
		close(pfd1[1]);
		dup2(pfd2[0],0);//3rd child's stdin=read end of fd2 i.e 
		if(execvp(progArgv[4],progArgv)==-1){
			printf("exevp: error \n");
			exit(-1);
		}
	}


	return 0;
}