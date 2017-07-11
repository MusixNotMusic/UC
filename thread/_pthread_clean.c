#include <apue.h>
#include <pthread.h>

void 
cleanup(void *arg)
{
	printf("cleanup: %s\n",(char *)arg);
}


/*
	function1 如果直接return函数， pthread没有执行cleanup函数，并且直接出现问题
	function2 如果使用pthread_exit函数， 在调用时 会将函数弹出栈，并执行调用

	pthread_cleanup_push  只用pthread_exit 才会从栈中调用 函数
*/ 
void *
thr_fn1(void *arg)
{
	printf("thread 1 start , arg = %d\n", (int) arg);
	pthread_cleanup_push(cleanup, "thread-1-1");
	pthread_cleanup_push(cleanup, "thread-1-2");
	printf("thread 1 push compeled\n");
	if(arg)
		return((void *)1);  // macos FREEBSD  出错
		// pthread_exit((void *)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return((void *)1);
}

void *
thr_fn2(void *arg)
{
	printf("thread 2 start , arg = %d\n", (int) arg);
	pthread_cleanup_push(cleanup, "thread-2-1");
	pthread_cleanup_push(cleanup, "thread-2-2");
	printf("thread 2 push compeled\n");
	if(arg)
		pthread_exit((void *)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}

int
main()
{
	int		err;
	pthread_t	tid1, tid2;
	void *tret;

	err = pthread_create(&tid1, NULL, thr_fn1, (void *)0);
	if(err != 0)
		err_quit("can't create thread 1: %s\n",strerror(err));

	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
	if(err != 0)
		err_quit("can't create thread 2: %s\n",strerror(err));

	// err = pthread_detach(tid1);// 分离线程 pthread_join 返回EINVAL
	// if(err != 0)
	// 	err_quit("can't detach thread 1: %s\n",strerror(err));


	err = pthread_join(tid1, &tret);
	if(err != 0)
		err_quit("can't join thread 1: %s\n",strerror(err));
	printf("thread 1 exit code %d\n",(int)tret);

	err = pthread_join(tid2, &tret);
	if(err != 0)
		err_quit("can't join thread 2: %s\n",strerror(err));
	printf("thread 2 exit code %d\n",(int)tret);
	exit(0);
}