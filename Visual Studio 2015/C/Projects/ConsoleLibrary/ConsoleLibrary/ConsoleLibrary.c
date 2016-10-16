#include<stdio.h>
#include<Windows.h>
#include"ConsoleLibrary.h"

void PrintCharacter(char Character, COORD Position, WORD Colors)
{
	CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleScreenBufferInfo);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Colors);
	putc(Character, stdout);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleScreenBufferInfo.wAttributes);
	return;
}

void DisplayCursor(void)
{
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursorInfo);
	return;
}

void HideCursor(void)
{
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursorInfo);
	return;
}
