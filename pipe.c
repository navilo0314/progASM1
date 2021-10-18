#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <sys/time.h>
int main(int argc, char* argv[]){
	int fd[2];
	//fd[0] read
	//fd[1] write 
	if (pipe(fd)==-1){
		printf("An error occured with opening the pipe\n");
		return 1;
	}
	int id=fork();
	//fd get copy over to the child pro
	//and can open or close independently 
	if(id==0){
		//child
		close(fd[0]);
		int x;
		printf("Input a number: ");
		scanf("%d\n",&x);
		printf("\nsending the number to y\n");
		if(write(fd[1],&x,sizeof(int))==-1){
			printf("An error occur when writing to the pipe\n");
			return 2;
		}
		//the data x is sent from fd[1] to fd[0]
		//after done writing close fd in this process
		close(fd[1]);
		printf("child terminated, sleep for 1s\n");
		sleep(1);
		return 1;
		//manage fd in each proc independently
	} 
	else{
		//no need write so close write end in parent
		wait(NULL);//wait for the child terminate
		close(fd[1]);
		int y;
		printf("y is reading the number\n");
		read(fd[0],&y,sizeof(int));
		close(fd[0]);//end of reading data
		printf("y=%d\n",y);
	}
}