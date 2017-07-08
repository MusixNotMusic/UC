#include <apue.h>
#include <errno.h>

void 
pr_mask(const char *str)
{
	sigset_t	set;
	int			errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &set) < 0)
		err_sys("sigprocmask error");
	printf("%s", str);

	if(sigismember(&set, SIGINT)) printf("SIGINT ");
	if(sigismember(&set, SIGQUIT)) printf("SIGQUIT ");
	if(sigismember(&set, SIGUSR1)) printf("SIGUSR1 ");
	if(sigismember(&set, SIGALRM)) printf("SIGALRM ");

	printf("\n");
	errno = errno_save;
}