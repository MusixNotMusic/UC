#include <apue.h>
#include "sig_sleep.c"

extern unsigned int sleep(unsigned int);
int
main(void)
{
	printf("sleep before\n");
	sleep(1);
	printf("sleep after 汉字\n");
}