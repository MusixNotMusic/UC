#include <apue.h>
#include <error.h>
#include <setjmp.h>

#define TOK_ADD 5
// #define MAXLINE 1024

jmp_buf	jmpbuffer;
void printOK(void);
void do_line(char *);
void throw(int);

int
main(void)
{
		char	line[MAXLINE];
		int 		code;
		if((code = setjmp(jmpbuffer)) != 0)
			printf("error code = %d\n",code);

		while(fgets(line, MAXLINE, stdin) != NULL)
			do_line(line);
		exit(0);
}

void 
do_line(char *line)
{
	char *str = "666";
	if((strlen(line)-1) ==7){
		printf("line--> %s\n", line );
		throw(1);
	}else{
		if(strstr(line, str) > 0){
			printOK();
		}
	}
}

void 
printOK(){
	printf("before 666 \n");
	throw(1001);
	printf("666 \n");
}

void
throw(int code)
{
	longjmp(jmpbuffer,code);
	exit(0);
}
