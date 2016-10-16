#ifndef CONSOLE_LIBRARY
#define CONSOLE_LIBRARY
#include<stdio.h>
#include<Windows.h>
#define cls() (system("cls"))

void PrintCharacter(char Character, COORD Position, WORD Colors);
COORD GetSize(void);
void DisplayCursor(void);
void HideCursor(void);
#endif
