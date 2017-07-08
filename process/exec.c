#include <apue.h>
#include <sys/wait.h>

char *env_init[] = {"USER=noknow", "PATH=/", NULL};

int
main(int argc, char *argv[]){
	pid_t pid;
	int i;
	char **ptr;
	extern char **environ;

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){ 
		if(execle("/bin/ls","" ,"/sbin","/bin", (char*)0, env_init) < 0)
			err_sys("execle error");
	}

	if(waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		printf("environment ===> here\n");
	for(i = 0; i < argc; i++)
		printf("argv[%d]: %s\n", i, argv[i]);
	for(ptr = environ; *ptr != 0; ptr++)
		printf("%s\n", *ptr);
		printf("\n");
		if(execlp("/bin/cat","" ,"exec.c", (char *)0) < 0)
			err_sys("execlp error");
	}
	exit(0);
}