#include	<limits.h>
#include	<stdio.h>
#include	<time.h>
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

int	WINAPI	WinMain
(
	HINSTANCE	hInstance,
	HINSTANCE	hPreInstance,
	LPSTR		lpszCmdLine,
	int			nCmdShow
)
{
	HWND		hMainWnd;
	MSG			Msg;
	WNDCLASS	MainWndClass;
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
	COLORREF	Color			=	BLACK;
	static	BOOL		FirstCall		=	TRUE;
	static	POINT		Point;
	static	RECT		Rect;
	static	BYTE		Direction		=	0;
	static	unsigned int	ChangeOfDirection	=	0;
		BYTE		ColorValue		=	GetRValue(Color);
	HDC			hDC;
	int			MaximumDifference,
				MinimumDifference;
	if(FirstCall)
	{
		size_t i;
		srand((unsigned)time(NULL));
		GetClientRect(hWnd, &Rect);
		Point.x		=	HALF(Rect.right);
		Point.y		=	HALF(Rect.bottom);
		ChangeOfDirection=123;
		FirstCall	=	FALSE;
	}
	hDC	=	GetDC(hWnd);
	Color	=	GetPixel
			(
			 	hDC,
				(int)Point.x,
				(int)Point.y
			);
	Color	=	RGB
			(
			 	GetRValue(Color)	+	BYTE_MAX / (sizeof(ChangeOfDirection) * CHAR_BIT),
			 	GetGValue(Color)	+	BYTE_MAX / (sizeof(ChangeOfDirection) * CHAR_BIT),
			 	GetBValue(Color)	+	BYTE_MAX / (sizeof(ChangeOfDirection) * CHAR_BIT)
			);
	SetPixel
	(
		hDC,
		(int)Point.x,
		(int)Point.y,
		Color
	);
	ReleaseDC
	(
		hWnd,
		hDC
	);
	if((1<<(GetRValue(Color)*sizeof(ChangeOfDirection)*CHAR_BIT/BYTE_MAX)&ChangeOfDirection))Direction++;
	else	Direction--;
	switch(Direction%4)
	{
		case	0:
			Point.y-=1;
			break;
		case	1:
			Point.x+=1;
			break;
		case	2:
			Point.y+=1;
			break;
		case	3:
			Point.x-=1;
	}
	if(Point.x	<	0)		Point.x	=	0;
	if(Point.y	<	0)		Point.y	=	0;
	if(Point.x	>	Rect.right)	Point.x	=	Rect.right;
	if(Point.y	>	Rect.bottom)	Point.y	=	Rect.bottom;
}
