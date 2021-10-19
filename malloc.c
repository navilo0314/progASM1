//malloc
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char*argv[]){
	/*int arr[3][3]={
		{1,2,3},
		{1,2,3},
		{1,2,3}
	};*/
	int i,j;
	int **arr=malloc(sizeof(int*)*3);
	for(i=0;i<3;i++){
		//arr[i] is a pointer still pointing to nothing
		arr[i]=malloc(sizeof(int)*3);
		//allocate memory for everything int*
		for(j=0;j<3;j++){
			arr[i][j]=j;
		}
	}
	printf("%lu\n",sizeof(arr)
		+sizeof(arr[0])*3+sizeof(int)*9);

}