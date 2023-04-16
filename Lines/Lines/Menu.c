
#include "Menu.h"
#include "Lines.h"

Button* buttons = NULL;

void DrawMenu()
{
	HWND hWnd = FindWindow(NULL, L"Lines");
	HWND hTextFont;
	HDC hdc = GetDC(hWnd);
	RECT r;
	GetClientRect(hWnd, &r);

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	HPEN hPen = CreatePen(BS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);

	Rectangle(hdc, r.left, r.top, r.right, r.bottom);

	if (buttons == NULL)
	{
		buttons = (Button*)realloc(buttons, 2 * sizeof(Button));
		buttons[0].x_centre_pos = r.right / 2;
		buttons[1].x_centre_pos = r.right / 2;

		buttons[0].y_centre_pos = (r.bottom - BTN_INDENT - BTN_HEIGHT) / 2;
		buttons[1].y_centre_pos = (r.bottom + BTN_INDENT + BTN_HEIGHT) / 2;

		sscanf(START, "%s", buttons[0].name);
		sscanf(QUIT, "%s", buttons[1].name);
	}

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	hTextFont = CreateFont(22, 0, 0, 0, FW_NORMAL, FALSE, 0, 0, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, L"Lucida Console");
	SelectObject(hdc, hTextFont);

	for (int i = 0; i < 2; i++)
	{
		ExtTextOutA(hdc, (buttons[i].x_centre_pos - BTN_WIDTH / 2 + BTN_WIDTH / strlen(buttons[i].name)), (buttons[i].y_centre_pos - BTN_HEIGHT / 2 + 10), NULL, &r, buttons[i].name, strlen(buttons[i].name), NULL);
	}
	DeleteObject(hTextFont);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void SelectButton(int btn_num, int last_btn)
{
	HWND hWnd = FindWindow(NULL, L"Lines");
	HWND hTextFont;
	HDC hdc = GetDC(hWnd);
	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	RECT r;

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	hTextFont = CreateFont(22, 0, 0, 0, FW_NORMAL, FALSE, 0, 0, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, L"Lucida Console");
	SelectObject(hdc, hTextFont);
	SelectObject(hdc, hPen);

	Rectangle(hdc, buttons[btn_num].x_centre_pos - BTN_WIDTH / 2, buttons[btn_num].y_centre_pos - BTN_HEIGHT / 2, buttons[btn_num].x_centre_pos + BTN_WIDTH / 2, buttons[btn_num].y_centre_pos + BTN_HEIGHT / 2);
	ExtTextOutA(hdc, (buttons[btn_num].x_centre_pos - BTN_WIDTH / 2 + BTN_WIDTH / strlen(buttons[btn_num].name)), (buttons[btn_num].y_centre_pos - BTN_HEIGHT / 2 + 10), NULL, &r, buttons[btn_num].name, strlen(buttons[btn_num].name), NULL);

	if (last_btn > -1)
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		Rectangle(hdc, buttons[last_btn].x_centre_pos - BTN_WIDTH / 2, buttons[last_btn].y_centre_pos - BTN_HEIGHT / 2, buttons[last_btn].x_centre_pos + BTN_WIDTH / 2, buttons[last_btn].y_centre_pos + BTN_HEIGHT / 2);
		ExtTextOutA(hdc, (buttons[last_btn].x_centre_pos - BTN_WIDTH / 2 + BTN_WIDTH / strlen(buttons[last_btn].name)), (buttons[last_btn].y_centre_pos - BTN_HEIGHT / 2 + 10), NULL, &r, buttons[last_btn].name, strlen(buttons[last_btn].name), NULL);
		DeleteObject(hBrush);
	}

	DeleteObject(hPen);
	DeleteObject(hTextFont);
	ReleaseDC(hWnd, hdc);
}