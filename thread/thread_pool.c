#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <assert.h>

typedef struct worker
{
	void * (*process)(void *arg);
	void * arg;
	struct worker *next;
} thread_worker;

typedef struct 
{
	pthread_mutex_t	queue_lock;
	pthread_cond_t	queue_ready;

	thread_worker *queue_head;

	int shutdown;

	pthread_t *tid;
	int max_thread_num;
	int cur_queue_size;
}thread_pool;


int pool_add_worker(void *(*process)(void *arg), void *arg);
void *thread_routine(void *arg);
void pool_init(int);
int pool_destroy(void);
static thread_pool *pool = NULL;

void 
pool_init(int max)
{
	pool = (thread_pool *)malloc(sizeof(thread_pool));
	pthread_mutex_init(&pool->queue_lock, NULL);
	pthread_cond_init(&pool->queue_ready, NULL);

	pool->max_thread_num = max;
    pool->cur_queue_size = 0;

	pool->queue_head = NULL;
	pool->shutdown = 0;
	
	//初始化 线程组
	pool->tid = (pthread_t *)malloc(sizeof(pthread_t) * max);
	int i = 0;
	for(i = 0; i < max; i++){
		pthread_create(&pool->tid[i], NULL, thread_routine, NULL);
	}
}

int
pool_add_worker(void *(*process)(void *arg), void *arg)
{
	thread_worker *worker = (thread_worker *)malloc(sizeof(thread_worker));
	worker->process = process;
	worker->arg = arg;
	worker->next = NULL;

	pthread_mutex_lock(&pool->queue_lock);

	thread_worker *mumber = pool->queue_head;
	if(mumber == NULL){
		pool->queue_head = worker;
	}else{
		while(mumber->next != NULL)
			mumber = mumber->next;
		mumber->next = worker;
	}
	assert (pool->queue_head != NULL);
	pool->cur_queue_size++;
	pthread_mutex_unlock(&pool->queue_lock);

	pthread_cond_signal(&pool->queue_ready);
	return pool->cur_queue_size;
}


int
pool_destroy(void)
{
	if(pool->shutdown)
		return -1;
	pool->shutdown = 1;

	pthread_cond_broadcast(&pool->queue_ready);

	int i;
	for (int i = 0; i < pool->max_thread_num; ++i)
		pthread_join(pool->tid[i], NULL);
	free(pool->tid);

	thread_worker *head = NULL;
	while(pool->queue_head != NULL){
		head = pool->queue_head;
		pool->queue_head = pool->queue_head->next;
		free(head);
	}

	pthread_mutex_destroy(&pool->queue_lock);
	pthread_cond_destroy(&pool->queue_ready);

	free(pool);
	pool = NULL;
	return 0;
}

void *
thread_routine(void *arg)
{
    printf("starting thread 0x%x\n", pthread_self());
    while(1)
    {
        pthread_mutex_lock(&(pool->queue_lock));
        /*如果等待队列为0并且不销毁线程池，则处于阻塞状态; 注意
        pthread_cond_wait是一个原子操作，等待前会解锁，唤醒后会加锁*/
        while(pool->cur_queue_size == 0 && !pool->shutdown)
        {
            printf("thread 0x%x is waiting\n", pthread_self());
            pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));
        }
        /*线程池要销毁了*/
        if(pool->shutdown)
        {
            /*遇到break,continue,return等跳转语句，千万不要忘记先解锁*/
            pthread_mutex_unlock(&(pool->queue_lock));
            printf ("thread 0x%x will exit\n", pthread_self());
            pthread_exit(NULL);
        }
        printf("thread 0x%x is starting to work\n", pthread_self());
        /*assert是调试的好帮手*/
        assert(pool->cur_queue_size != 0);
        assert(pool->queue_head != NULL);
        
        /*等待队列长度减去1，并取出链表中的头元素*/
        pool->cur_queue_size--;
        thread_worker *worker = pool->queue_head;
        pool->queue_head = worker->next;
        pthread_mutex_unlock(&(pool->queue_lock));
        /*调用回调函数，执行任务*/
        (*(worker->process))(worker->arg);
        free(worker);
        worker = NULL;
    }
    /*这一句应该是不可达的*/
    pthread_exit(NULL);
}

void pool_wait()
{

}

void *
myprocess(void *arg)
{
    printf("threadid is 0x%x, working on task %d\n", pthread_self (),*(int *) arg);
    // sleep(1);/*休息一秒，延长任务的执行时间*/
    return NULL;
}
int
main(int argc, char **argv)
{
    pool_init(4);/*线程池中最多三个活动线程*/
    
    /*连续向池中投入10个任务*/
    int *workingnum = (int *) malloc (sizeof(int) * 10);
    int i;
    for (i = 0; i < 10; i++)
    {
        workingnum[i] = i;
        pool_add_worker (myprocess, &workingnum[i]);
    }
    sleep(5);
    /*等待所有任务完成*/
    /*销毁线程池*/
    pool_destroy();
    free(workingnum);
    return 0;
}

