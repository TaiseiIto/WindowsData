#include<stdio.h>
#include<stdlib.h>
#include"MyLibrary.h"
int main(void)
{
	char *buf1=input(),*buf2=input();
	printf(stristr(buf1,buf2));
	free(buf1);
	free(buf2);
	return EXIT_SUCCESS;
}