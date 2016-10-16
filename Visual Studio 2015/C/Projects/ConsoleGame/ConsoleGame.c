#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"ConsoleLibrary.h"

int main(void)
{
	HideCursor();
	while(true)if(_kbhit())
	{
	}
	return EXIT_SUCCESS;
}
