#include<Windows.h>
#include"WindowsAPILibrary.h"

LRESULT CALLBACK WindowProcedure
(
	HWND	hWindow,
	UINT	Message,
	WPARAM	wPalam,
	LPARAM	lPalam
);

int WINAPI WinMain
(
	HINSTANCE	hInstance,
	HINSTANCE	hPreInstance,
	LPSTR		lpszCommandLine,
	int			nCommandToShow
)
{
	char		szClassName[] = "Window Class Name";
	HWND		hWindow;
	MSG			Message;
	WNDCLASS	WindowClass;
	if (!hPreInstance)
	{
		WindowClass.cbClsExtra		= 0;
		WindowClass.cbWndExtra		= 0;
		WindowClass.hbrBackground	= CreateSolidBrush(RGB(0, 0, 0));
		WindowClass.hCursor			=	LoadCursor
										(
											NULL,
											IDC_ARROW
										);
		WindowClass.hIcon			= NULL;
		WindowClass.hInstance		= hInstance;
		WindowClass.lpfnWndProc		= WindowProcedure;
		WindowClass.lpszClassName	= szClassName;
		WindowClass.lpszMenuName	= NULL;
		WindowClass.style			=	CS_HREDRAW|
										CS_VREDRAW;
		if (!RegisterClass(&WindowClass))return EXIT_FAILURE;
	}
	hWindow =	CreateWindow
				(
					szClassName,
					"window title",
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
	ShowWindow
	(
		hWindow,
		nCommandToShow
	);
	UpdateWindow(hWindow);
	while
	(
		GetMessage
		(
			&Message,
			NULL,
			0,
			0
		)
	)
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return EXIT_SUCCESS;
}

LRESULT CALLBACK WindowProcedure
(
	HWND	hWindow,
	UINT	Message,
	WPARAM	wPalam,
	LPARAM	lPalam
)
{
	switch (Message)
	{
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		break;
	case WM_PAINT:
	{
		HDC hDeviceContext;
		RECT Rect;
		DRAWTEXTPARAMS DrawTextParams;
		PAINTSTRUCT PaintStruct;
		GetClientRect
		(
			hWindow,
			&Rect
		);
		DrawTextParams.cbSize		= sizeof(DRAWTEXTPARAMS);
		DrawTextParams.iLeftMargin	= 0;
		DrawTextParams.iRightMargin	= 0;
		DrawTextParams.iTabLength	= 10;
		hDeviceContext =	BeginPaint
							(
								hWindow,
								&PaintStruct
							);
		ShowText
		(
			hDeviceContext,
			"Hello\tWorld!",
			&Rect,
			CreateFont
			(
				100,
				100,
				100,
				100,
				100,
				FALSE,
				TRUE,
				TRUE,
				ANSI_CHARSET,
				OUT_CHARACTER_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH,
				"‚l‚r –¾’©"
			),
			0,
			RGB(255, 0, 0),
			RGB
			(
				0x00,
				0x00,
				0x00
			),
			TRANSPARENT,
			DT_WORDBREAK|
			DT_EDITCONTROL|
			DT_EXPANDTABS|
			DT_NOPREFIX|
			DT_CENTER|
			DT_VCENTER,
			&DrawTextParams
		);
		EndPaint
		(
			hWindow,
			&PaintStruct
		);
		break;
	}
	default:
		return	DefWindowProc
				(
					hWindow,
					Message,
					wPalam,
					lPalam
				);
	}
	return EXIT_SUCCESS;
}
