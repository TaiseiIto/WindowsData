#include<windows.h>

int WINAPI WinMain
(
 	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow
)
{
	MessageBox
	(
		NULL,
		"Hello,World!",
		"MessageBox",
		MB_OK
	);
	return EXIT_SUCCESS;
}

