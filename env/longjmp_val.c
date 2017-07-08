#include <apue.h>
#include <error.h>
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2(void);
static jmp_buf	jmpbuf;
static int		globalval;

int
main()
{
	int 				autoval;
	register int		regival;
	volatile int 	volaval;	
	static 	 int		statval;

	autoval = 1; regival = 2; volaval = 3; statval = 4; globalval = 5;

	if(setjmp(jmpbuf) != 0){
		printf("after longjmp ------ : )\n");
		printf("autoval = %d; regival = %d; volaval = %d; statval = %d; globalval = %d  \n",
		autoval, regival, volaval, statval, globalval);
		exit(0);
	}

	autoval = 100; regival = 200; volaval = 300; statval = 400; globalval = 500;

	f1(autoval, regival, volaval, statval);
	exit(0);
}

static void 
f1(int a, int b, int c, int d)
{
	printf("in f1():\n");
	printf("autoval = %d; regival = %d; volaval = %d; statval = %d; globalval = %d    \n",
		a, b, c, d, globalval);
	f2();
}

static void
f2(void)
{
	longjmp(jmpbuf, 1);
}