#include <apue.h>

Sigfunc *
signal(int signo, Sigfunc* func)
{
	struct sigaction  act, oact;

	act.as_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
#ifdef  SA_INTERRUPT
	act.flag |= SA_INTERRUPT;
#endif
	if(sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return oact.sa_handler;
}