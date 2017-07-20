#include <apue.h>
#include <pthread.h>

#define fn void* (*)((void*))
int	quitflag;
sigset_t	mask;

pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	pwait =  PTHREAD_COND_INITIALIZER;

void *
thr_fn(void *arg)
{
	int err, signo;

	for(;;){
		err = sigwait(&mask, &signo);
		printf("callback wait there\n");
		if(err != 0)
			err_exit(err, "sigwait failed");
		switch(signo){
			case SIGINT:
			printf("\ninterrupt\n");
			break;
			case SIGQUIT:
			pthread_mutex_lock(&lock);
			quitflag = 1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&pwait);
			return(0);

			default:
			printf("unexpected signal %d\n", signo);
			exit(1);
		}
	}
}

int
main(void)
{
	int err;
	sigset_t	oldmask;
	pthread_t tid;
	int concurrency;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);

	if((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
		err_exit(err,"SIG_BLOCK ERROR");
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if(err != 0)
		err_exit(err,"can't create thread");

	pthread_mutex_lock(&lock);
	while(quitflag == 0){
		printf("pthread wait there\n");
		pthread_cond_wait(&pwait, &lock);
	}
	pthread_mutex_unlock(&lock);

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");

	concurrency = pthread_getconcurrency();
	printf("concurrency level = %d\n", concurrency);
	exit(0);
}