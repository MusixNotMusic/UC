#include <apue.h>
#include <error.h>
#include <fcntl.h>
int
main(void)
{
	if(creat("666",O_CREAT | O_RDWR)<0)
		err_sys("fcntl.h creat error");
	sleep(5);
	if(rename("666","yes") < 0)
		err_quit("stdio.h rename error");
	exit(0);
}