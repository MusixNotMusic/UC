#include <apue.h>
#include <error.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	int fd;
	printf("argv[1] = %s, argv[2] = %s\n",argv[1], argv[2] );
	if((fd = open(argv[1], O_CREAT| O_RDWR, S_IRUSR| S_IWUSR | S_IRGRP | S_IWGRP)) <0 )
		err_sys("fcntl.c open error");


	printf("%s %d %d\n", argv[2] ,  strlen(argv[2]) ,sizeof(argv[2])/sizeof(char) );
	if(write(fd, argv[2], strlen(argv[2]))<0)
		err_sys("stdio.h write error ");

	close(fd);
	exit(0);

}