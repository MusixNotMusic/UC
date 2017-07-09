#include <apue.h>

volatile	sig_atomic_t	quitflag;

static void 
sig_int(int signo)
{
	if(signo == SIGINT)
		printf("\ninterrupt :) \n");
	else if(signo == SIGQUIT)
		quitflag = 1;
}

int
main(void)
{
	sigset_t	newmask, oldmask, zeromask;
	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	if(signal(SIGQUIT, sig_int) == SIG_ERR)
		err_sys("signal(SIGQUIT) error");

	sigemptyset(&newmask);
	sigemptyset(&zeromask);
	sigaddset(&newmask, SIGQUIT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");

	while(quitflag == 0)
		sigsuspend(&zeromask);
	quitflag = 0;
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK for oldmask error");
	printf("end print ? oldmask = %d, newmask = %d, zeromask = %d", oldmask, newmask, zeromask);
	exit(0);
}