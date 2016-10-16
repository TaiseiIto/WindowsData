#pragma once
#pragma comment(lib, "ConsoleLibrary.lib")
#include<stdio.h>
#include<Windows.h>
#define cls() system("cls")

void PrintCharacter(char Character, COORD Position, WORD Colors);
void DisplayCursor(void);
void HideCursor(void);