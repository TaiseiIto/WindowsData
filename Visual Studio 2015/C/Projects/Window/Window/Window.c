#include<Windows.h>

LPCSTR lpszMainWndClass = "main window class";
LPCSTR lpszMainWndTitle = "main window title";

LRESULT CALLBACK MainWndProc
(
	HWND	hWnd,
	UINT	uiMsg,
	WPARAM	wParam,
	LPARAM	lParam
);

int WINAPI WinMain
(
	HINSTANCE	hInstance,
	HINSTANCE	hPreInstance,
	LPSTR		lpszCmdLine,
	int			nCmdShow
)
{
	HWND		hWnd;
	MSG			Msg;
	WNDCLASS	WndClass;
	WndClass.cbClsExtra		= 0;
	WndClass.cbWndExtra		= 0;
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor		=	LoadCursor
								(
									NULL,
									IDC_ARROW
								);
	WndClass.hIcon			=	LoadIcon
								(
									NULL,
									IDI_APPLICATION
								);
	WndClass.hInstance		= hInstance;
	WndClass.lpfnWndProc	= MainWndProc;
	WndClass.lpszClassName	= lpszMainWndClass;
	WndClass.lpszMenuName	= NULL;
	WndClass.style			=	CS_HREDRAW|
								CS_VREDRAW;
	if(!RegisterClass(&WndClass))return EXIT_FAILURE;
	hWnd =	CreateWindow
			(
				lpszMainWndClass,
				lpszMainWndTitle,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				NULL,
				NULL,
				hInstance,
				NULL
			);
	if(hWnd == NULL)return EXIT_FAILURE;
	ShowWindow
	(
		hWnd,
		nCmdShow
	);
	while
	(
		GetMessage
		(
			&Msg,
			NULL,
			0,
			0
		)
	)DispatchMessage(&Msg);
	return (int)Msg.wParam;
}

LRESULT CALLBACK MainWndProc
(
	HWND	hWnd,
	UINT	uiMsg,
	WPARAM	wParam,
	LPARAM	lParam
)
{
	switch(uiMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		break;
	}
	return	DefWindowProc
			(
				hWnd,
				uiMsg,
				wParam,
				lParam
			);
}