#include <apue.h>
#define semptyset(ptr)	(*(ptr) = 0)
#define sfillset(ptr)	(*(ptr) = ~(sigset_t)0, 100)

int
main()
{
	int *p,ret;
	semptyset(p);
	printf("size = %lu\n", sizeof(sigset_t));
	printf("p = %u\n", *p);
	ret = sfillset(p);
	printf("p = %u, ret = %d\n",*p, ret);
	printf("bool = %d\n", 2>1);
	printf("bool = %d\n", 0>1);
	exit(0);
}