#include<stdio.h>
#include<stdlib.h>
#include"MyLibrary.h"
#include"FileLibrary.h"

size_t FileSize(char *FileName)
{
	size_t returned;
	FILE *FilePointer;
	fopen_s(&FilePointer, FileName, ReadMode);
	if (FilePointer == NULL)return 0;
	fseek(FilePointer, 0, SEEK_END);
	returned = (size_t)ftell(FilePointer);
	fclose(FilePointer);
	return returned;
}

array GetFileData(char *FileName, size_t Point, size_t Length)
{
	array returned;
	FILE *FilePointer;
	size_t i;
	fopen_s(&FilePointer, FileName, ReadMode);
	if (FilePointer == NULL || FileSize(FileName) < Point + Length)
	{
		returned.Size = 0;
		returned.Data = NULL;
		return returned;
	}
	returned.Size = Length;
	returned.Data = (byte*)calloc_s(Length, sizeof(char));
	fseek(FilePointer, (long)Point, SEEK_SET);
	for (i = 0; i < Length; i++)returned.Data[i] = getc(FilePointer);
	fclose(FilePointer);
	return returned;
}

int OverwriteFileData(char *FileName, size_t Point, array Data)
{
	FILE *FilePointer;
	array FileContent = GetFileData(FileName, 0, FileSize(FileName)),NewFileContent;
	size_t i;
	NewFileContent.Size = (FileContent.Size < Point + Data.Size)? Point + Data.Size: FileContent.Size;
	NewFileContent.Data = (byte*)calloc_s(NewFileContent.Size, sizeof(byte));
	for (i = 0; i < FileContent.Size; i++)NewFileContent.Data[i] = FileContent.Data[i];
	for (i = Point; i < Point + Data.Size; i++)NewFileContent.Data[i] = Data.Data[i - Point];
	fopen_s(&FilePointer, FileName, WriteMode);
	if (FilePointer == NULL)return EXIT_FAILURE;
	for (i = 0; i < NewFileContent.Size; i++)putc(NewFileContent.Data[i], FilePointer);
	fclose(FilePointer);
	free(NewFileContent.Data);
	return EXIT_SUCCESS;
}

int InsertFileData(char *FileName, size_t Point, array Data)
{
	FILE *FilePointer;
	array FileContent = GetFileData(FileName, 0, FileSize(FileName)), NewFileContent;
	size_t i;
	NewFileContent.Size = (FileContent.Size < Point)? Point + Data.Size: FileContent.Size + Data.Size;
	NewFileContent.Data = (byte*)calloc_s(NewFileContent.Size, sizeof(byte));
	for (i = 0; i < Point; i++)NewFileContent.Data[i] = FileContent.Data[i];
	for (i = Point; i < Point + Data.Size; i++)NewFileContent.Data[i] = Data.Data[i - Point];
	for (i = Point + Data.Size; i < NewFileContent.Size; i++)NewFileContent.Data[i] = FileContent.Data[i - Data.Size];
	fopen_s(&FilePointer, FileName, WriteMode);
	if (FilePointer == NULL)return EXIT_FAILURE;
	for (i = 0; i < NewFileContent.Size; i++)putc(NewFileContent.Data[i], FilePointer);
	fclose(FilePointer);
	free(NewFileContent.Data);
	return EXIT_SUCCESS;
}

int DeleteFileData(char *FileName, size_t Point, size_t Length)
{
	FILE *FilePointer;
	array FileContent = GetFileData(FileName, 0, FileSize(FileName)), NewFileContent;
	size_t i;
	if (Point >= FileContent.Size)return EXIT_SUCCESS;
	NewFileContent.Size = (Point + Length > FileContent.Size)? Point: FileContent.Size - Length;
	NewFileContent.Data = (byte*)calloc_s(NewFileContent.Size, sizeof(byte));
	for (i = 0; i < Point; i++)NewFileContent.Data[i] = FileContent.Data[i];
	for (i = Point; i < NewFileContent.Size; i++)NewFileContent.Data[i] = FileContent.Data[i + Length];
	fopen_s(&FilePointer, FileName, WriteMode);
	if (FilePointer == NULL)return EXIT_FAILURE;
	for (i = 0; i < NewFileContent.Size; i++)putc(NewFileContent.Data[i], FilePointer);
	fclose(FilePointer);
	free(NewFileContent.Data);
	return EXIT_SUCCESS;
}
