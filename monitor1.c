//this program will handle 2 processes connected with ! 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
int main(int argc, char* argv[]){
	char* prog1Argv[]={"./add","3","5",NULL};
	char* prog2Argv[]={"./multiplyBy4",NULL};
	//hardcoding the command arg but be ./monitor1 ./add 3 5 ! multiplyBy4
	int fd[2];
	pipe(fd);
	
	//creaet child process to handle the prog1
	if (fork()==0){
		printf("Parent create first child\n");
		//child process which 
		close(fd[0]);//we only need to write stuff 
		//build dup2 connection from the stdout of prog1 to the fd[1]
		dup2(fd[1],STDOUT_FILENO);
		//close(fd[1]);//close the write end of fd
		//build dup2 already and then we can do the exec of prog1 
		if(execvp("./add",prog1Argv)  ==-1){//not working but why 
			printf("error in execvp first prog\n");
			exit(-1);

		}
	}
	if (fork()==0){
		//second prog 
		printf("parent create 2nd child ");//
		close(fd[1]);//close the write end of the pipe 
		//connect the stdin of prog2 to the read end of fd 
		dup2(fd[0],STDIN_FILENO);
		if(execvp("./multiplyBy4",prog2Argv)==-1){
			printf("error in execvp in 2nd prog\n");
			exit(-1);
		}
	}
	return 0;
}