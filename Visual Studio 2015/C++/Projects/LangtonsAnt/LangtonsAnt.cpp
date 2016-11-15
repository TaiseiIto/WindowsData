#include	<iostream>
#include	<string>
#include	<ctime>
#include	<Windows.h>
#include	"MathLibrary.h"
#define		BLACK								(RGB(0,0,0))
#define		BYTE_MAX							(0xff)
#define		BYTE_MIN							(0x00)
#define		HALF(X)								((X)/2)
#define		MAIN_WINDOW_POSITION_X				(0)
#define		MAIN_WINDOW_POSITION_Y				(0)
#define		NO_EXTRA							(0)
#define		NO_MSG_FILTER						(0)
#define		NO_STYLE							(0)
#define		MAIN_WND_CLASS						"LangtonsAnt window class"
#define		MAIN_WND_TITLE						"LangtonsAnt"

LRESULT	CALLBACK	MainWndProc
(
	HWND	hWnd,
	UINT	uiMsg,
	WPARAM	wParam,
	LPARAM	lParam
);

void	LangtonsAnt(HWND	hWnd);

MathLibrary::Bits ChangeOfDirection;

int	WINAPI	WinMain
(
	HINSTANCE	hInstance,
	HINSTANCE	hPreInstance,
	LPSTR		lpszCmdLine,
	int		nCmdShow
)
{
	HWND		hMainWnd;
	MSG			Msg;
	WNDCLASS	MainWndClass;
	std::string	strCmdLine		=	lpszCmdLine;
	ChangeOfDirection			=	strCmdLine;
	MainWndClass.cbClsExtra			=	NO_EXTRA;
	MainWndClass.cbWndExtra			=	NO_EXTRA;
	MainWndClass.hbrBackground		=	(HBRUSH)GetStockObject(BLACK_BRUSH);
	MainWndClass.hCursor			=	LoadCursor
										(
											NULL,
											IDC_ARROW
										);
	MainWndClass.hIcon				=	LoadIcon
										(
											hInstance,
											"RANDOMWALK_ICON"
										);
	MainWndClass.hInstance			=	hInstance;
	MainWndClass.lpfnWndProc		=	MainWndProc;
	MainWndClass.lpszClassName		=	MAIN_WND_CLASS;
	MainWndClass.lpszMenuName		=	NULL;
	MainWndClass.style				=	NO_STYLE;
	if(!RegisterClass(&MainWndClass))return	EXIT_FAILURE;
	hMainWnd	=	CreateWindow
					(
						MAIN_WND_CLASS,
						MAIN_WND_TITLE,
						WS_POPUP,
						MAIN_WINDOW_POSITION_X,
						MAIN_WINDOW_POSITION_Y,
						GetSystemMetrics(SM_CXSCREEN),
						GetSystemMetrics(SM_CYSCREEN),
						NULL,
						NULL,
						hInstance,
						NULL
					);
	if(hMainWnd	==	NULL)return	EXIT_FAILURE;
	ShowWindow
	(
		hMainWnd,
		nCmdShow
	);
	while(TRUE)
		if
		(
			PeekMessage
			(
				&Msg,
				NULL,
				NO_MSG_FILTER,
				NO_MSG_FILTER,
				PM_NOREMOVE
			)
		)
			if
			(
				GetMessage
				(
					&Msg,
					NULL,
					NO_MSG_FILTER,
					NO_MSG_FILTER
				)
			)
				DispatchMessage(&Msg);
			else	return (int)Msg.wParam;
		else	LangtonsAnt(hMainWnd);
	return (int)Msg.wParam;
}

LRESULT	CALLBACK	MainWndProc
(
	HWND	hWnd,
	UINT	uiMsg,
	WPARAM	wParam,
	LPARAM	lParam
)
{
	static	POINT	FirstMouseCursorPosition;
			POINT	MouseCursorPosition;
	switch(uiMsg)
	{
	case	WM_CREATE:
		GetCursorPos(&FirstMouseCursorPosition);
		ShowCursor(FALSE);
		return	EXIT_SUCCESS;
	case	WM_DESTROY:
		ShowCursor(TRUE);
		PostQuitMessage(EXIT_SUCCESS);
		return	EXIT_SUCCESS;
	case	WM_KEYDOWN:
	case	WM_LBUTTONDOWN:
	case	WM_MBUTTONDOWN:
	case	WM_RBUTTONDOWN:
		GetCursorPos(&MouseCursorPosition);
		PostMessage
		(
			hWnd,
			WM_SYSCOMMAND,
			SC_CLOSE,
			(LPARAM)(MouseCursorPosition.x|(MouseCursorPosition.y<<0x10))
		);
		return	EXIT_SUCCESS;
	}
	return	DefWindowProc
			(
				hWnd,
				uiMsg,
				wParam,
				lParam
			);
}

void	LangtonsAnt(HWND		hWnd)
{
	static	BYTE		**ColorStep;
	static	BOOL		FirstCall		=	TRUE;
	static	POINT		Point;
	static	RECT		Rect;
	static	BYTE		Direction		=	0;
	HDC			hDC;
	int			MaximumDifference,
				MinimumDifference;
	MathLibrary::Bits	One			=	MathLibrary::Bits("1");
	if(FirstCall)
	{
		size_t i;
		srand((unsigned)time(NULL));
		GetClientRect(hWnd, &Rect);
		Point.x		=	HALF(Rect.right);
		Point.y		=	HALF(Rect.bottom);
		ColorStep	=	new BYTE*[Rect.right];
		for(int i = 0; i < Rect.right; i++)ColorStep[i] = new BYTE[Rect.bottom];
		for(int i = 0; i < Rect.right; i++)for(int j = 0; j < Rect.bottom; j++)ColorStep[i][j]=0;
		FirstCall	=	FALSE;
	}
	hDC		=	GetDC(hWnd);
	if(((One << ColorStep[Point.x][Point.y] & ChangeOfDirection) >> ColorStep[Point.x][Point.y]).getBit(0))Direction++;
	else	Direction--;
	ColorStep[Point.x][Point.y] += 1;
	if(ColorStep[Point.x][Point.y] == ChangeOfDirection.getSize())ColorStep[Point.x][Point.y] = 0;
	SetPixel
	(
		hDC,
		(int)Point.x,
		(int)Point.y,
		RGB
		(
		 	ColorStep[Point.x][Point.y] * BYTE_MAX / (ChangeOfDirection.getSize() - 1),
		 	ColorStep[Point.x][Point.y] * BYTE_MAX / (ChangeOfDirection.getSize() - 1),
		 	ColorStep[Point.x][Point.y] * BYTE_MAX / (ChangeOfDirection.getSize() - 1)
		)
	);
	ReleaseDC
	(
		hWnd,
		hDC
	);
	switch(Direction%4)
	{
		case	0:
			if(Point.y == Rect.top + 1)	Point.y	=	Rect.bottom - 1;
			else				Point.y-=1;
			break;
		case	1:
			if(Point.x == Rect.left + 1)	Point.x	=	Rect.right - 1;
			else				Point.x-=1;
			break;
		case	2:
			if(Point.y == Rect.bottom - 1)	Point.y	=	Rect.top + 1;
			else				Point.y+=1;
			break;
		case	3:
			if(Point.x == Rect.right - 1)	Point.x	=	Rect.left + 1;
			else				Point.x+=1;
	}
	return;
}
