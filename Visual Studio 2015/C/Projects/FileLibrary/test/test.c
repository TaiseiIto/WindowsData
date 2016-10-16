#include<stdio.h>
#include<stdlib.h>
#include"FileLibrary.h"

int main(void)
{
	size_t i;
	for (i = 0; i < FileSize("test.txt"); i++)printf("%c", GetFileData("test.txt", 0, FileSize("test.txt")).Data[i]);
	return EXIT_SUCCESS;
}