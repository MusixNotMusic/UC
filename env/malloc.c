#include <apue.h>
#include <error.h>
struct _int_2
{
	int *a;
	int b;
};
int 
main(void)
{	
	int num = 356;
	int num1 = 200;
	int num2 = 97;
	struct _int_2 * two = (struct _int_2 *)malloc(sizeof(char *) * 2);
	two->a = &num;
	two->b =  num1;
	printf("two->a %d two->b %d\n", *two->a, two->b);
	printf("two->a  address 0x%x |  num address 0x%x\n",two->a, &num );
	char *c = ((char *)two->a);
	*(c+1) = two->b;
	*(c+2) = num2;
	printf("character = %s\n", c);
	return(0);
}