#include<stdio.h>
#include<stdlib.h>
#ifdef	_WIN64
#define	TEXT "x64"
#elif	_WIN32
#define	TEXT "x86"
#endif

int main(void)
{
	printf("%s\n", TEXT);
	return EXIT_SUCCESS;
}