#include<stdio.h>
#include<Windows.h>

int main(void)
{
	CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_screen_buffer_info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN|FOREGROUND_RED);
	printf("Hello,World!");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), console_screen_buffer_info.wAttributes);
	{
		COORD a;
		a.X = 10;
		a.Y = 100;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), a);
	}
	return EXIT_SUCCESS;
}