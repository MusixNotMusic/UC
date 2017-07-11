#include <apue.h>
#include <stdlib.h>
// v8 random 
double 
v8_random()
{
	int rngstate[2];
	int r0 = (18030*(rngstate[0] & 0xFFFF)) + ((rngstate[0] >> 16) | 0);
	rngstate[0] = r0;
	int r1 = (36969*(rngstate[1] & 0xFFFF)) + ((rngstate[1] >> 16) | 0);
	rngstate[1] = r1;
	int x = ((r0 << 16) + (r1 & 0xFFFF)) | 0;
	double  rand = (x < 0 ? (x + 0x100000000) : x) * 2.3283064365386962890625e-10;
	return rand;
}

int
main(void)
{
	double ran = v8_random();
	printf("random = %.16lf\n", ran);
	exit(0);
}


