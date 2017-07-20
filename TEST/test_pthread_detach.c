#include <apue.h>
// #include <time.h>  
#include <sys/time.h>
#include "../thread_ctnl/pthread_detach.c"

extern int makethread(void * (*)(void *), void *);

void 
fn(int time)
{
	printf("this thread id is ===> 0x%x \n", pthread_self());
	// printf("time ===> %d \n", time);
}

int
main(void)
{
	int err;
	// struct  timeval    tv;
    // gettimeofday(&tv,NULL);
	err = makethread(fn, NULL);
	if(err!=0)
		err_sys("makethread err");
	return(0);
}