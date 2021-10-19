#include <stdio.h>
#include <stdlib.h>
int main(int argc, char*argv[]){
	//argv=={"add.c","3","5"}
	int result=0;
	result+=atoi(argv[1])+atoi(argv[2]);
	//done of adding 
	printf("%d",result);
	return 0;
}