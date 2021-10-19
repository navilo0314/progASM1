#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char*argv[]){
	
	//int redirect_fd=open("op.txt",O_CREAT|O_TRUNC|O_WRONLY);
	int fd[2];//fd[0] read end 
			  //fd[1] write end
	//open pipe
	pipe(fd);
	if (fork()==0){//parent create a child process.  
		printf("successfully create a child process\n");
		//This child process is printing smth to stdout and redirect stdout 
		//To the write end of fd i.e fd[1] 		
		close(fd[0]);//close the read end 
		dup2(fd[1],STDOUT_FILENO);//this somehow replaced the write(fd[1],,)
		//connect the stdout to write end of fd
		printf("%c",'a');
		close(fd[1]);//close write end of fd[1] in child process
	}
	else{
		//parent process
		char char_got_from_stdin;
		close(fd[1]);
		char message;//this is just a string 
		//read(fd[0],&message,sizeof(char));
		dup2(fd[0],STDIN_FILENO);//connect the fd[0] into the stdin of this parent 
		//1. setup dup2 connection 
		//2. get input by scanf 
		//printf("The message got from the read end of fd is: \n%c\n",message);
		scanf("%c",&char_got_from_stdin);
		printf("The char received from stdin is %c\n",char_got_from_stdin);

	}
	return 0;
}