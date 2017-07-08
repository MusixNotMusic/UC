#include <stdio.h>
#define pr(name,func) pr_number(#name, name,func)
#define null (void*)0

#define SIG_DFL (void (*) (int))0
#define SIG_DFL_1 (void (*) ())'a'
#define LO (void (*)()) 10

void pr_number(char *, int, void(*func)());

int
main(void)
{

	int OK;
	int Yes;
	OK = 1;
	Yes = 666;
	printf("LO %d\n", LO);
	pr(OK,SIG_DFL);
	// pr(Yes,LO);
	if(null == NULL)
	printf("ok\n");
	else
	printf("no\n");

	printf("macro 0 = %d, NULL = %d\n", SIG_DFL, NULL);
	printf("macro 1 = %d, void 0 = %d \n", SIG_DFL_1,(void*)0);
	exit(0);
}

void 
pr_number(char *name, int num, void(*func)())
{
	// printf("func = %d \n", func());
	func();
	printf("name = %s, num = %d\n",name, num);
}