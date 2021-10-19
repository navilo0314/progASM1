//we will implement the split function in this prog
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <fcntl.h>

void printArgv_2d(int argc, char ***argv_2d);
void calculateNumberOfProg(int &numberOfProgs,int arc, char*arv[]);

int main(int argc, char* argv[])  {
	
	for(int i=0;i<argc;i++){//just print all element in argv
		printf("%s\n",argv[i]);
	}
	//Find the number of programs to be executed 
	int numOfProgs=1;
	calculateNumberOfProg(&numOfProgs,argc,argv);
	
	return 0;
}
void printArgv_2d(int argc, char***argv_2d){
	int j=0;
	int k=0;
	for(int i=1;i<argc;i++){
		if(argv_2d[j][k]==NULL){
			printf("\n");
			j++;
			k=0;
		}
		else{
			printf("%s ",argv_2d[j][k]);
		}
		k++;
	}
	return;
}
void calculateNumberOfProg(int &numberOfProgs,int arc, char*arv[]){
	for(int i=0;i<arc,i++){//iterate argv
		if(arv[i]=="!"){
			numberOfProgs++;
		}
	}
}












