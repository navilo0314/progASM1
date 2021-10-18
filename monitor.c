#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
void printProgArgv(int count, char* argv[]);
const char* TerminationStatus(int status);
//float calculateUserTime(struct timeval start, struct timeval finish);

void sigIntHandling(int num){
	printf("detect sigInt\n");
	return; 
}
int main(int argc, char* argv[]){
	int fd[2];//used for sending start time from child to parent process
	int execSucess;

	if (argc>1){//if there is a program to be executed
		printf("There are %d command argument for the monitor\n",argc);
		char* progArgv[argc-1];// this array of string will be passed to the prog to be exec
		for (int i=0;i<argc-1;i++){//update the entity of progArgv by the 2nd element to the last element of argv
			printf("i=%d\n",i);
			progArgv[i]=argv[i+1];
			progArgv[i]=argv[i+1];
		}
		progArgv[argc-1]=NULL;

		printProgArgv(argc-1,progArgv);//debug
		if (pipe(fd)==-1){//open a pipe
			printf("Error occured with opening pipe\n");
			return 1;
		}
		int pid=fork();//create child process
		
		if(pid<0){//case: failed in creating child process
			printf("Fork() failed\n");
			exit(-1);
		}
		else if(pid==0){//child process
			printf("child process created\n");
			//Process with id: 12557 created for the command: xxxxx
			printf("Process with id: %d created for the command: %s\n",getpid(),argv[1]);
			close(fd[0]);//close read end of pipe
			struct timeval progStartTime;
			gettimeofday(&progStartTime,NULL);	//get wallclock time
			//send the start time of the prog to the parent 
			write(fd[1],&progStartTime,sizeof(progStartTime));//write start time to the pipe
			close(fd[1]);//end of writing to the pipe, close pipe
			if (execvp(argv[1], progArgv)==-1){
				execSucess=-1;
				printf("exec: : No such file or directory\n");
				return 1;
			}
				//failed in exec prog
			else{execSucess=1;}

			//   argv== {"./monitor","./hello",NULL}
			printf("execvp() Failed"); 
			exit(-1);
		}
		else 
		{	
		// Parent Process
			//handle sigint and sent sigint to the child process 
			int status;
			int options;
			struct timeval start,finish;//for calculate the usertime
			long page_fault;
			long context_switch;
			struct rusage rus; //GET system,user time and  context switch 

			signal(SIGINT,SIG_IGN);//ignore sigint signal 
			wait4(pid,&status,options,&rus);
			//get the wallclock finish time of the program 
			gettimeofday(&finish,NULL);	//get wallclock time
			//read the wallclock start time of the prog from the pipe
			read(fd[0],&start,sizeof(start));
			close(fd[0]);//close the read end of pipe;
			close(fd[1]);//close the write end of pipe
			double realFinishTime = (double)finish.tv_sec+ (double)finish.tv_usec*1e-6;
			double realStartTime=(double)start.tv_sec+(double)start.tv_usec*1e-6;
    		double realTime=realFinishTime-realStartTime;
    		double userTime=(double)rus.ru_utime.tv_sec+(double)+rus.ru_utime.tv_usec*1e-6;
    		double sysTime=(double)rus.ru_stime.tv_sec+(double)+rus.ru_stime.tv_usec*1e-6;
    		//getTerminationStatus(status);
    		printf("The command \"%s\" is interrupted by the signal number = %d %s\n",
    			argv[1],status,TerminationStatus(status));

    		printf("real: %.3f s, user: %.3f s, system: %.3f s\n",realTime,userTime,sysTime);
			printf("no. of page faults: %ld\n",page_fault);
			printf("no. of context switches: %ld\n",context_switch);
			printf("exit status: %d\n",status);

			printf("\n");
		}
	}
	else{
		printf("No prog to be executed\n");
	}
	return 0;
}
/*float calculateUserTime(struct timeval start, struct timeval finish){
	//float startTime=start.tv_sec+(start.tv_usec/100000);
	printf("start time is %f\n",startTime);
	return finish-start;
}*/
void printProgArgv(int count, char* argv[]){
	printf("printing entities of progArgv\n");
	for(int i=0;i<count;i++){
		printf("%s ",argv[i]);
	}
	printf("\n");
}
const char* TerminationStatus(int status){
	if (status==0) return "";
	else if (status==1) return "(SIGHUP)";
	else if (status==2) return "(SIGINT)";
	else if (status==3) return "(SIGQUIT)";
	else if (status==4) return "(SIGILL)";
	else if (status==5) return "(SIGTRAP)";
	else if (status==6) return "(SIGABRT)";
	else if (status==8) return "(SIGFPE)";
	else if (status==11) return "(SIGSEGV)";
	else if (status==13) return "(SIGPIPE)";
	else if (status==14) return "(SIGALRM)";
	else if (status==2) return "(SIGTERM)";
	else return "";

}