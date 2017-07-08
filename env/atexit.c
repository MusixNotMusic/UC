#include <apue.h>
#include <error.h>

#include <pthread.h>
void  exit1(void );
void  exit2(void );

pthread_t tid;


void 
exit1()
{
	tid = pthread_self();
	printf("exit 1  tid = 0x%x\n", (unsigned int) tid);	
}
void 
exit2( )
{
	tid = pthread_self();
	printf("exit 2 tid = 0x%x\n", (unsigned int)tid);
}

int
main(void)
{
	int err;
	tid = pthread_self();
	if(atexit(exit1)  != 0)
		err_sys("can't register exit1");
	if(atexit(exit2) != 0)
		err_sys("can't regoster exit2");
	if(atexit(exit2) != 0)
		err_sys("can't regoster exit2");
	if(atexit(exit1)  != 0)
		err_sys("can't register exit1");

	exit1();
	exit2();

	// err = pthread_create(&tid, NULL, exit1,  NULL);
	// if(err != 0)
	// 	err_quit("can't create thread: %s\n", strerror(err));
	printf("main is done tid = 0x%x\n", (unsigned int)tid);
	exit(0);
}