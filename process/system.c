#include <apue.h>
#include <sys/wait.h>
#include "my_exit.c"

extern void pr_exit(int);

int 
main(void)
{
	int status;

	if((status = system("date")) < 0)
		err_sys("system() error");
	pr_exit(status);

	if((status = system("pwd")) < 0)
		err_sys("system() error");
	pr_exit(status);

	if((status = system("who; exit 200")) < 0)
		err_sys("system() error");
	pr_exit(status);


	exit(0);
}