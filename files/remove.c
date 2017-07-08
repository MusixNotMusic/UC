#include <apue.h>
#include <error.h>


int 
main()
{
	if(remove("test")<0)
		err_ret("stdio.h remove error");
	exit(0);
}