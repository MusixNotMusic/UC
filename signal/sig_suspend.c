#include <apue.h>
#include "pr_sig.c"

extern void pr_mask(const char *);
static void sig_int(int);
int
main(void)
{
	sigset_t	newmask, oldmask, waitmask;

	pr_mask("program start: ");

	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	sigemptyset(&waitmask);
	sigaddset(&waitmask,SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	printf("set newmask = 0x%x, set waitmask = 0x%x\n",newmask, waitmask);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");

	pr_mask("in critical region: ");

	if(sigsuspend(&waitmask) != -1)
		err_sys("sigsuspend error");

	pr_mask("after return from sigsuspend ");

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");

	printf("set oldmask = %d\n",oldmask);
	pr_mask("program exit: ");
}

static void
sig_int(int signo)
{
	pr_mask("\nin sig_int: ");
}
