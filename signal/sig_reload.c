#include <apue.h>
#include <pwd.h>

static void
my_alarm(int signo)
{
	struct passwd  *rootptr;

	printf("in signal handler, signo = %d\n", signo);
	if((rootptr = getpwnam("musix")) == NULL)
		err_sys("getpwnam(musix) error");
	printf("musix ==> %s, musix.passwd ===> %s\n", rootptr->pw_name,  rootptr->pw_passwd);
	alarm(1);
}

int
main(void)
{
	struct passwd	*ptr;

	signal(SIGALRM, my_alarm);
	alarm(1);

	for(;;){
		if((ptr = getpwnam("root")) == NULL)
			err_sys("getpwnam error");
		if(strcmp(ptr->pw_name, "musix") != 0)
			printf("return value corrupted!, pw_name = %s, pw_passwd = %s\n",ptr->pw_name,ptr->pw_passwd);
	}
}