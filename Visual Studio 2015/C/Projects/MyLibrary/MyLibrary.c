#include<ctype.h>
#include <stdio.h>	//for "getchar"
#include <stdlib.h>	//for "malloc" and "free"
#include <string.h>
#include <time.h>
#include "MyLibrary.h"

void* calloc_s(size_t _Count, size_t _Size)
{
	void* pointer = calloc(_Count, _Size);
	if (pointer == NULL)
	{
		printerr("This program stoped because of the memory allocation error!\n");
		exit(EXIT_FAILURE);
	}
	return pointer;
}

char* get_string(FILE* file/*"getstring" reads from it*/, char character_of_end/*When it is found, "gestring" will stop reading*/)
{
	char *string = calloc_s(1, sizeof(char))/*It will be returned*/, *backup_string/*During "string" is invalid, the data will be stored here.*/, character/*input character will be stored here*/;
	size_t string_size = 1/*size of "string"*/, i/*for "for loop"*/;
	string[0] = '\0';
	while ((character = getc(file)) != character_of_end)//character from "file" is stored and checked. 
	{
		//preparing "backup_string"
		backup_string = calloc_s(string_size - 1, sizeof(char));
		for (i = 0; i < string_size - 1; i++)backup_string[i] = string[i];

		//preparing new "string"
		free(string);
		string_size++;
		string = calloc_s(string_size, sizeof(char));

		//transcribing data
		for (i = 0; i < string_size - 2; i++)string[i] = backup_string[i];

		//freeing "backup_string"
		free(backup_string);

		//adding "character"
		string[string_size - 2] = character;

		//adding '\0'
		string[string_size - 1] = '\0';
	}
	return string;
}

char *input()
{
	char *returned = get_string(stdin,'\n');
	return returned;
}

size_t file_size(FILE* file)
{
	size_t size/*It will be returned.*/, position = (size_t)ftell(file)/*Position of cursor is stored in it.*/;
	fseek(file, 0L, SEEK_END);
	size = (size_t)ftell(file);
	fseek(file, (long)position, SEEK_SET);
	return size;
}

int my_rand(int min, int max)
{
	return rand()%(max-min+1)+min;
}

char *strtoupper(char *string)
{
	char *returned;
	size_t string_length = 0, i;
	while(string[string_length]!='\0')string_length++;
	returned = calloc_s(string_length+1, sizeof(char));
	for(i = 0; i <= string_length; i++)returned[i]=toupper(string[i]);
	return returned;
}

char *strtolower(char *string)
{
	char *returned;
	size_t string_length = 0, i;
	while(string[string_length]!='\0')string_length++;
	returned = calloc_s(string_length+1, sizeof(char));
	for(i = 0; i <= string_length; i++)returned[i]=tolower(string[i]);
	return returned;
}

char *stristr(char *string, char *substring)
{
	char	*lowerstring	=	strtolower(string),
			*lowersubstring	=	strtolower(substring),
			*lowerreturned	=	strstr(lowerstring, lowersubstring);
	if(lowersubstring == NULL)return NULL;
	return lowerreturned - lowerstring + string;
}
