#ifndef MY_LIBRARY
#define MY_LIBRARY
#include<ctype.h>
#include <stdio.h>	//for "getchar"
#include <stdlib.h>	//for "malloc" and "free"
#include <string.h>
#include <time.h>
#include "MyLibrary.h"
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
//it Prints to stderr.
#define printerr(format,...) fprintf(stderr,format, __VA_ARGS__)
#ifndef _WINDOWS_
typedef char byte;
#endif
typedef struct
{
	byte *Data;
	size_t Size;
} array;
//Dynamic allocation used in "get_string"
void* calloc_s(size_t _Count, size_t _Size);
//it reads "file" untill it find "character_of_end" and returns readed string.
char* get_string(FILE* file, char character_of_end);
//It reads "stdin".
char *input();
//it returns the size of "file".
size_t file_size(FILE* file);

int my_rand(int min, int max);

char *strtoupper(char *string);

char *strtolower(char *string);

char *stristr(char *str, char *substr);
#endif
