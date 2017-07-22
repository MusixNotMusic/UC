#include <apue.h>
#include <fcntl.h>
#include "../signal/sig_notify.c"

extern void TELL_WAIT(void);
extern void TELL_PARENT(pid_t pid);
extern void WAIT_PARENT(void);
extern void TELL_CHILD(pid_t pid);
extern void WAIT_CHILD(void);


int
lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock	lock;

	lock.l_type = type;		/* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_start = offset;	/* byte offset, relative to l_whence */
	lock.l_whence = whence;	/* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len;		/* #bytes (0 means to EOF) */

	return( fcntl(fd, cmd, &lock) );	/* -1 upon error */
}

static void
lockabyte(const char *name, int fd, off_t offset)
{
	if(writew_lock(fd, offset, SEEK_SET, 1) < 0)
		err_sys("%s: writew_lock error", name);
	printf("%s: got the lock, byte %lld\n", name, offset);
}

int 
main(void)
{
	int	fd;
	pid_t	pid;
	if((fd = creat("templock",FILE_MODE)) < 0)
		err_sys("creat error");
	if(write(fd, "ab", 2) != 2)
		err_sys("write error");

	TELL_WAIT();

	if((pid = fork()) < 0){
		err_sys("fork error");
	}
	else if(pid == 0){
		lockabyte("child", fd, 0);
		TELL_PARENT(getppid());
		WAIT_PARENT();
		lockabyte("child", fd, 0);
	}
	else{
		lockabyte("parent", fd, 1);
		TELL_CHILD(pid);
		WAIT_CHILD();
		lockabyte("parent", fd, 0);
	}
	exit(0);
}