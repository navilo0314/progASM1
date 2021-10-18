#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

void print_cpu_time()
{
 struct rusage usage;
 getrusage (RUSAGE_SELF, &usage);
 printf ("CPU time: %ld.%03ld sec user, %ld.%03ld sec system\n",
     usage.ru_utime.tv_sec, (long)usage.ru_utime.tv_usec,
     usage.ru_stime.tv_sec, (long)usage.ru_stime.tv_usec);
}
int main(){
	print_cpu_time();
	return 0;
}