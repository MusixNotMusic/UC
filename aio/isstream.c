#include <apue.h>
#include <fcntl.h>
// #include <stropts.h>
// #include "stream.c"

// extern int isastream(int fd);

// 判断是否是流设备 
// BSD linux Solaris : int isatty(fd);
// linux Solaris: int isastream(fd);  头文件 在#include <stropts.h>
 

int
main(int argc, char *argv[])
{
	int	i,fd;
	for(i = 1; i < argc; i++)
	{
		if((fd = open(argv[i], O_RDONLY)) < 0){
			err_ret("%s: can't open", argv[i]);
			continue;
		}
		if(isatty(fd) == 0)
		// if(isastream(fd) == 0)
			err_ret("%s: not a stream", argv[i]);
		else
			err_msg("%s: stream device", argv[i]);
	}
	exit(0);
}