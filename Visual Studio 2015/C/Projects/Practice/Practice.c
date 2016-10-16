#include<stdio.h>
#include<stdlib.h>

typedef int bool;

static bool true = 1;
static bool false = 0;

int main(void)
{
	int c = getchar();
	bool thereIsASpace = false;
	while(c != EOF)
	{
		if(c != ' ' && c != '\t' && c != '\n')putchar(c);
		if((c == ' ' || c == '\t' || c == '\n') && !thereIsASpace)putchar(' ');
		if(c != ' ' && c != '\t' && c != '\n')thereIsASpace = false;
		if(c == ' ' || c == '\t' || c == '\n')thereIsASpace = true;
		c = getchar();
	}
	return EXIT_SUCCESS;
}
