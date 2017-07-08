#include <apue.h>

int 
main(void)
{
	printf("real uid = %d, effect uid = %d\n",getuid(), geteuid());
	exit(0);
}