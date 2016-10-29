#include	<limits.h>
#include	<stdio.h>
#include	<time.h>
#include	<Windows.h>
#include	"MyLibrary.h"
#define		BLACK								(RGB(0,0,0))
#define		BYTE_MAX							(0xff)
#define		BYTE_MIN							(0x00)
#define		HALF(X)								((X)/2)
#define		MAIN_WINDOW_POSITION_X				(0)
#define		MAIN_WINDOW_POSITION_Y				(0)
#define		MAX_DIFFERENCE_OF_CURSOR_POSITION	(10)
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

int		NomalMode
(
	HINSTANCE	hInstance,
	HINSTANCE	hPreInstance,
	LPSTR		lpszCmdLine,
	int			nCmdShow
);

int		PreviewMode
(
	HINSTANCE	hInstance,
	HINSTANCE	hPreInstance,
	LPSTR		lpszCmdLine,
	int			nCmdShow,
	HWND	hWnd
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
	HANDLE		Mutex	=	CreateMutex
							(
								NULL,
								TRUE,
								"LangtonsAnt mutex"
							);
	if(GetLastError()	==	ERROR_ALREADY_EXISTS)return	EXIT_SUCCESS;
	if(!_stricmp(__argv[1],"/s")||!_stricmp(__argv[1],"-s"))return	NomalMode
																	(
																		hInstance,
																		hPreInstance,
																		lpszCmdLine,
																		nCmdShow
																	);
	if(!_stricmp(__argv[1],"/p")||!_stricmp(__argv[1],"-p"))return	PreviewMode
																	(
																		hInstance,
																		hPreInstance,
																		lpszCmdLine,
																		nCmdShow,
																		(HWND)atoll(__argv[2])
																	);
	if
	(
		stristr
		(
			__argv[1],
			"/c"
		)	==	__argv[1]	||
		stristr
		(
			__argv[1],
			"-c"
		)	==	__argv[1]
	)
	MessageBox
	(
		NULL,
		"ê›íËéñçÄÇÕÇ†ÇËÇ‹ÇπÇÒÅB",
		"LangtonsAnt",
		MB_OK
	);
	return	EXIT_SUCCESS;
}

int		NomalMode
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

int		PreviewMode
(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpszCmdLine,
	int			nCmdShow,
	HWND	hWnd
)
{
	return	EXIT_SUCCESS;
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
	{
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
	case	WM_MOUSEMOVE:
		GetCursorPos(&MouseCursorPosition);
		if(abs((int)(MouseCursorPosition.x-FirstMouseCursorPosition.x))>MAX_DIFFERENCE_OF_CURSOR_POSITION||abs((int)(MouseCursorPosition.y-FirstMouseCursorPosition.y))>MAX_DIFFERENCE_OF_CURSOR_POSITION)
		{
			PostMessage
			(
				hWnd,
				WM_SYSCOMMAND,
				SC_CLOSE,
				(LPARAM)(MouseCursorPosition.x|(MouseCursorPosition.y<<0x10))
			);
			return	EXIT_SUCCESS;
		}
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
		for(i = 0; i < sizeof(ChangeOfDirection)	*	CHAR_BIT; i++)
		{
			ChangeOfDirection	<<=	1;
			ChangeOfDirection	+=	(unsigned int)my_rand
							(
						 		0,
								1
							);
		}
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
