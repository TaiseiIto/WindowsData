#pragma once
#pragma comment(lib, "FileLibrary.lib")
#include<stdio.h>
#include<stdlib.h>
#include"MyLibrary.h"

static const char *ReadMode	= "r";
static const char *WriteMode	= "w";
size_t FileSize(char *FileName);
array GetFileData(char *FileName, size_t Point, size_t Length);
int OverwriteFileData(char *FileName, size_t Point, array Data);
int InsertFileData(char *FileName, size_t Point, array Data);
int DeleteFileData(char *FileName, size_t Point, size_t Length);