#include <apue.h>

static void sig_quit(int);

int
main(void)
{
	sigset_t	newmask, oldmask, pendmask;

	if(signal(SIGQUIT, sig_quit) == SIG_ERR)
		err_sys("signal error");
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("sigprocmask error");
	printf("newmask = %x, oldmask = %x\n",newmask, oldmask);
	sleep(5);

	if(sigpending(&pendmask) < 0)
		err_sys("sigpending error");

	if(sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");

	printf("SIGQUIT unblocked oldmask = %d\n", (int)oldmask);
	sleep(5);
	exit(0);
}

static void
sig_quit(int signo)
{
	printf("caugh SIGQUIT\n");
	if(signal(SIGQUIT,SIG_DFL) == SIG_ERR)
		err_sys("can't reset SIGQUIT");
}