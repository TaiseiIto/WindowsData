#ifndef WINDOWS_API_LIBRARY
#define WINDOWS_API_LIBRARY
#include<Windows.h>

void ShowText
(
	HDC					hDeviceContext,
	LPCSTR				Text,
	LPRECT				lpRect,
	HFONT				Font,
	int					CharacterExtra,
	COLORREF			ForeColor,
	COLORREF			BackgroundColor,
	int					BackgroundMode,
	UINT				dwDrawTextFormat,
	LPDRAWTEXTPARAMS	lpDrawTextParams
);
#endif
