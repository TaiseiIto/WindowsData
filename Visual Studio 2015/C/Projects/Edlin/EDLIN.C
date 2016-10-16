#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"MyLibrary.h"

size_t fileLines(const char *fileContent);
size_t whereIsNthBackslashN(const char *fileContent, size_t n);
char *getNthLine(const char *fileContent, size_t n);

int main(int argc, char **argv)
{
	char *command = NULL;
	char *fileName;
	char *fileContent = NULL;
	FILE *file;
	if(argc != 2)
	{
		printerr("\aThe commend syntax is \"EDLIN filename\".\n");
		return EXIT_FAILURE;
	}
	fileName = argv[1];
	file = fopen(fileName, "r");
	if(file == NULL)printf("New file\n");
	else
	{
		fileContent = get_string(file, EOF);
		fclose(file);
		printf("End of input file\n");
	}
	while(TRUE)
	{
		putchar('*');
		while(command == NULL || strlen(command) == 0)command = input();
		switch(command[strlen(command) - 1])
		{
		case 'L':
		case 'l':
			break;
		case 'I':
		case 'i':
			break;
		case 'D':
		case 'd':
			break;
		case 'E':
		case 'e':
			break;
		case 'Q':
		case 'q':
			free(fileContent);
			return EXIT_SUCCESS;
		//default:
		}
		free(command);
		command = NULL;
	}
}

size_t fileLines(const char *fileContent)
{
	size_t fileLines = 0;
	size_t readPosition = 0;
	while(fileContent[readPosition] != '\0')if(fileContent[readPosition++] == '\n')fileLines++;
	return fileLines;
}

size_t whereIsNthBackslashN(const char *fileContent, size_t n)
{
	size_t whereIsNthBackslashN = 0;
	size_t backslashCount = 0;
	if(n >= fileLines(fileContent))
	{
		printerr("n >= fileLines(fileContent) @ size_t wheleIsNthBackslashN(const char *fileContent, size_t n)\n");
		return 0;
	}
	while(backslashCount < n)if(fileContent[whereIsNthBackslashN++] == '\n')backslashCount++;
	return whereIsNthBackslashN;
}

char *getNthLine(const char *fileContent, size_t n)
{
	char *getNthLine;
	size_t getNthLineSize;
	int i;
	if(n > fileLines(fileContent))
	{
		printerr("n > fileLines(fileContent) @ char *getNthLine(const char *fileContent, size_t n)\n");
		return NULL;
	}
	if(n == fileLines(fileContent))getNthLineSize = strlen(fileContent) - whereIsNthBackslashN(fileContent, n - 1);
	else getNthLineSize = whereIsNthBackslashN(fileContent, n) - whereIsNthBackslashN(fileContent, n - 1);
	getNthLine = calloc_s(getNthLineSize, sizeof(char));
	for(i = 0; i < getNthLineSize - 1; i++)getNthLine[i] = fileContent[whereIsNthBackslashN(fileContent, n - 1) + i];
	getNthLine[getNthLineSize - 1] = '\0';
	return getNthLine;
}

