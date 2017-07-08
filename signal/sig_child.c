#include <apue.h>
#include <sys/wait.h>

// #if defined(BSD) || defined(MACOS)
#define SIGCLD  SIGCHLD
// #endif
static void sig_cld(int);


int
main()
{
	pid_t	pid;
	// printf("SIGCHLD = %d, SIGCLD = %d\n",SIGCHLD,SIGCLD );
	if(signal(SIGCLD, sig_cld) == SIG_ERR)
		perror("signal error");
	if((pid = fork()) < 0){
		perror("fork error");
	}else if(pid == 0){
		sleep(2);
		_exit(0);
	}
	pause();
	exit(0);
}

static void
sig_cld(int signo)
{
	pid_t	pid;
	int 	status;

	printf("SIGCLD recevied\n");
	if(signal(SIGCLD, sig_cld) == SIG_ERR)
		perror("signal error");

	if((pid = wait(&status)) < 0)
		perror("wait error");
	printf("pid = %d\n", pid);
}