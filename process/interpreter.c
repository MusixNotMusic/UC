#include <apue.h>
#include <sys/wait.h>

int
main(void)
{
	pid_t	pid;
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		// if(execl("/Users/musix/Desktop/ll","interprete","/home","/bin",(char *)0))
		// 	err_sys("execl error");
		if(execl("/Users/musix/Desktop/Myworkspace/UNIX C/666/sh/awkkk","interprete","/home","/bin","666","hehe",(char *)0))
			err_sys("execl error");
	}
	printf("lllasdsda \n");
	if(waitpid(pid, NULL, 0) < 0)
		err_sys("waitpid error");
	exit(0);
}