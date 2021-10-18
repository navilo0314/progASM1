#include <stdio.h>
#include <sys/time.h>   // for gettimeofday()
#include <unistd.h>     // for sleep()
 
// main function to find the execution time of a C program
int main()
{
    struct timeval start, end;
 
    gettimeofday(&start, NULL);
 
    // do some stuff here
    sleep(4);
 
    gettimeofday(&end, NULL);
 
    long seconds = (end.tv_sec - start.tv_sec);
    long startmicros = (start.tv_usec);
    long endmicros = (end.tv_usec);

    printf("start micros: %ld; end mircos: %ld\n",startmicros,endmicros);
    //printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
  //  printf("fseconds: %f\n",fseconds);
    return 0;
}

