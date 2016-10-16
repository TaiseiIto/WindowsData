#include<Windows.h>
#include"WindowsAPILibrary.h"

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
)
{
	SelectObject
	(
		hDeviceContext,
		Font
	);
	SetTextCharacterExtra
	(
		hDeviceContext,
		CharacterExtra
	);
	SetTextColor
	(
		hDeviceContext,
		ForeColor
	);
	SetBkColor
	(
		hDeviceContext,
		BackgroundColor
	);
	SetBkMode
	(
		hDeviceContext,
		BackgroundMode
	);
	DrawTextEx
	(
		hDeviceContext,
		Text,
		-1,
		lpRect,
		dwDrawTextFormat,
		lpDrawTextParams
	);
	return;
}
