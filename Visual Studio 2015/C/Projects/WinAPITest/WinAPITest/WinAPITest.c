#include<Windows.h>

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
	MSG			msg;
	WNDCLASS	WndClass;
	LPCTSTR		lpszMainWndClass	= "main window class";
	LPCTSTR		lpszMainWndTitle	= "main window title";
	WndClass.cbClsExtra		= 0;
	WndClass.cbWndExtra		= 0;
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
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
				WS_OVERLAPPEDWINDOW|
				WS_HSCROLL|
				WS_VSCROLL,
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
			&msg,
			NULL,
			0,
			0
		)
	)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
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
	case WM_CREATE:
		CreateWindow(
			TEXT("STATIC") , "ˆÉ“¡@‘¾´\nˆÉ“¡@‘¾´" ,
			WS_CHILD | WS_VISIBLE | SS_CENTER ,
			100 , 100 , 200 , 45 ,
			hWnd , (HMENU)1 ,
			((LPCREATESTRUCT)(lParam))->hInstance , NULL
		);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		break;
	case WM_PAINT:
	{
		int x,y;
		PAINTSTRUCT	PaintStruct;
		HBRUSH		hBrush	=	CreateHatchBrush
								(
									HS_DIAGCROSS,
									RGB
									(
										0x00,
										0x00,
										0xff
									)
								);
		HPEN		hPen	=	CreatePen
								(
									PS_SOLID,
									10,
									RGB
									(
										0xff,
										0x00,
										0x00
									)
								);
		HDC			hdc		=	BeginPaint
								(
									hWnd,
									&PaintStruct
								);
		HRGN		hrgn;
		RECT		rect;
		TEXTMETRIC tm;
		TCHAR str[64];
		rect.left	=0;
		rect.top	=0;
		rect.right	=100;
		rect.bottom	=100;
		hrgn		=CreateRectRgnIndirect(&rect);
		SelectObject(hdc, (HGDIOBJ)hPen);
		SelectObject(hdc, (HGDIOBJ)hBrush);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor
		(
			hdc,
			RGB
			(
				0xff,
				0xff,
				0xff
			)
		);
		for(x = 0; x < 0x200; x++)
			for(y = 0; y < 0x200; y++)
				if((0x100-x)*(0x100-x)+(0x100-y)*(0x100-y)<0x100*0x100)
				SetPixel
				(
					hdc,
					x,
					y,
					RGB
					(
						x,
						y,
						0xff
					)
				);
		Chord(hdc,10,10,210,210,0,0,0,500);
		FrameRgn(hdc,hrgn,hBrush,10,20);
		GetTextMetrics(hdc , &tm);
		wsprintf(str , "‰¡• %d px" , GetDeviceCaps(hdc , HORZRES));
		TextOut(hdc , 10 , 10 , str , lstrlen(str));
		wsprintf(str , "‚‚³ %d px" , GetDeviceCaps(hdc , VERTRES));
		TextOut(hdc , 10 , 10 + tm.tmHeight , str , lstrlen(str));
		EndPaint
		(
			hWnd,
			&PaintStruct
		);
		DeleteObject(hPen);
		DeleteObject(hBrush);
		DeleteObject(hrgn);
		break;
	}
	case WM_CHAR:
		MessageBox(hWnd,(LPCSTR)&wParam,"",MB_OK);
		break;
	case	WM_HSCROLL:

	case WM_MOUSEMOVE:
	if(wParam & MK_LBUTTON)
	{
		HDC hdc = GetDC(hWnd);
		int wMouseX = LOWORD(lParam),wMouseY = HIWORD(lParam);
		RECT ClientRect;
		GetClientRect(hWnd, &ClientRect);
		int x,y;
			for(x = 0; x < ClientRect.right; x++)
			for(y = 0; y < ClientRect.bottom; y++)
				if((x-wMouseX)*(x-wMouseX)+(y-wMouseY)*(y-wMouseY)<0x100)
				SetPixel
				(
					hdc,
					x,
					y,
					RGB
					(
						x,
						y,
						0xff
					)
				);
		ReleaseDC(hWnd,hdc);
	}
	break;
	case WM_KILLFOCUS:
	{
		HDC hdc = GetDC((HWND)wParam);
		int x,y;
		for(x = 0; x < 0x200; x++)
			for(y = 0; y < 0x200; y++)
				if((0x100-x)*(0x100-x)+(0x100-y)*(0x100-y)<0x100*0x100)
				SetPixel
				(
					hdc,
					x,
					y,
					RGB
					(
						x,
						y,
						0xff
					)
				);
		ReleaseDC((HWND)wParam,hdc);
		break;
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
