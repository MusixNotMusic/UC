#include <stdio.h>
#include <png.h>
#include <unistd.h>
void print_clean_up(void);
void print_clean_down(void);
int
main()
{
	int j=0, ret;

	setbuf(stdout, NULL);
    while(j++<10)
    {
               printf("这是第%d----\n",j);
               printf("这是第%d----\n",j);
               sleep(1);
               print_clean_up();
               print_clean_up();
    }
    // printf("666"); 
    // sleep(2);
    // printf("\b"); 
    return(0);
}

void
print_clean_up(){
	printf("\r\033[1A");
}

void 
print_clean_down(){
	printf("\033[XB");
	printf("\r");
}
