#include <apue.h>

static void
sig_alrm(int signo)
{
	printf("sleep in alrm\n");
}

unsigned int
sleep(unsigned int nsec)
{
	struct 		sigaction	newact, oldact;
	sigset_t	newmask, oldmask, suspmask;
	unsigned int	unslept;

	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM, &newact, &oldact);

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK,&newmask, &oldmask);

	alarm(nsec);

	suspmask = oldmask;
	sigdelset(&suspmask,SIGALRM);
	sigsuspend(&suspmask);

	unslept = alarm(0);

	sigaction(SIGALRM, &oldact, NULL);
	sigprocmask(SIG_SETMASK, &suspmask,NULL);
	return (unslept);	
}