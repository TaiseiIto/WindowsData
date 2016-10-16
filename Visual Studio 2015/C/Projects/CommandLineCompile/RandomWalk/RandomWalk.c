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
#define		MAIN_WND_CLASS						"RandomWalk window class"
#define		MAIN_WND_TITLE						"RandomWalk"

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

void	RandomWalk(HWND	hWnd);

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
								"RandomWalk mutex"
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
		"RandomWalk",
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
		else	RandomWalk(hMainWnd);
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

void	RandomWalk(HWND		hWnd)
{
	static	COLORREF	Color		=	BLACK;
	static	BOOL		FirstCall	=	TRUE;
	static	POINT		Point;
	static	RECT		Rect;
			BYTE		Red			=	GetRValue(Color),
						Green		=	GetGValue(Color),
						Blue		=	GetBValue(Color);
			HDC			hDC;
			int			MaximumDifference,
						MinimumDifference;
	if(FirstCall)
	{
		srand((unsigned)time(NULL));
		GetClientRect(hWnd, &Rect);
		Point.x		=	HALF(Rect.right);
		Point.y		=	HALF(Rect.bottom);
		FirstCall	=	FALSE;
	}
	hDC	=	GetDC(hWnd);
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
	MaximumDifference	=	1;
	MinimumDifference	=	-1;
	Point.x	+=	(LONG)	my_rand
						(
							MinimumDifference,
							MaximumDifference
						);
	Point.y	+=	(LONG)	my_rand
						(
							MinimumDifference,
							MaximumDifference
						);
	if(Point.x	<	0)				Point.x	=	0;
	if(Point.y	<	0)				Point.y	=	0;
	if(Point.x	>	Rect.right)		Point.x	=	Rect.right;
	if(Point.y	>	Rect.bottom)	Point.y	=	Rect.bottom;
	switch(Red)
	{
	case	BYTE_MIN:
		MinimumDifference	=	0;
		MaximumDifference	=	1;
		break;
	case	BYTE_MAX:
		MinimumDifference	=	-1;
		MaximumDifference	=	0;
		break;
	default:
		MinimumDifference	=	-1;
		MaximumDifference	=	1;
	}
	Red	+=	(BYTE)	my_rand
					(
						MinimumDifference,
						MaximumDifference
					);
	switch(Green)
	{
	case	BYTE_MIN:
		MinimumDifference	=	0;
		MaximumDifference	=	1;
		break;
	case	BYTE_MAX:
		MinimumDifference	=	-1;
		MaximumDifference	=	0;
		break;
	default:
		MinimumDifference	=	-1;
		MaximumDifference	=	1;
	}
	Green	+=	(BYTE)	my_rand
						(
							MinimumDifference,
							MaximumDifference
						);
	switch(Blue)
	{
	case	BYTE_MIN:
		MinimumDifference	=	0;
		MaximumDifference	=	1;
		break;
	case	BYTE_MAX:
		MinimumDifference	=	-1;
		MaximumDifference	=	0;
		break;
	default:
		MinimumDifference	=	-1;
		MaximumDifference	=	1;
	}
	Blue	+=	(BYTE)	my_rand
						(
							MinimumDifference,
							MaximumDifference
						);
	Color	=	RGB
				(
					Red,
					Green,
					Blue
				);
}
