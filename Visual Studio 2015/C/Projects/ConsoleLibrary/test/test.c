#include<stdio.h>
#include<Windows.h>
#include"ConsoleLibrary.h"

int main(void)
{
	COORD Position;
	Position.X = 50;
	Position.Y = 20;
	PrintCharacter('a', Position, FOREGROUND_BLUE|BACKGROUND_RED);
	Position.X = 1;
	Position.Y = 1;
	PrintCharacter('a', Position, FOREGROUND_GREEN | BACKGROUND_BLUE);
	HideCursor();
	DisplayCursor();
	cls();
	return EXIT_SUCCESS;
}