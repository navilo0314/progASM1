#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]){//argc should be 9 
	printf("this is the hello prog\n");
	printf("argc is %d\n",argc);
	//int *p=NULL;
	//*p=11;//segvault
	//while(1){
		for(int i=0;i<argc;i++){
			printf("The %dth command arg of hello is %s\n",i,argv[i]);
			sleep(1);
		}
	//}	
	return 0;
}