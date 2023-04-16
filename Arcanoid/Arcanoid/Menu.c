#include "Events.h"

Button* SystemInit(Button* buttons)
{
	buttons = (Button*)calloc(BTN_NUM, sizeof(Button));
	for (int i = 0; i < BTN_NUM; i++)
	{
		buttons[i].centre_pos.x = WINDOW_WIDTH / 2;
		memset(buttons[i].name, 0, NAME_SIZE);
		
		if (i == 0)
		{
			sscanf(START, "%s", buttons[i].name);
			buttons[i].centre_pos.y = FIELD_HEIGHT / 2 - BTN_HEIGHT - BTN_INDENT;
		}
		if (i == 1)
		{
			sscanf(OPTIONS, "%s", buttons[i].name);
			buttons[i].centre_pos.y = FIELD_HEIGHT / 2;
		}
		if (i == 3)
		{
			sscanf(EASY, "%s", buttons[i].name);
			buttons[i].centre_pos.y = FIELD_HEIGHT / 2 - BTN_HEIGHT - BTN_INDENT;
		}
		if (i == 4)
		{
			sscanf(MEDIUM, "%s", buttons[i].name);
			buttons[i].centre_pos.y = FIELD_HEIGHT / 2;
		}
		if (i == 5)
		{
			sscanf(HARD, "%s", buttons[i].name);
			buttons[i].centre_pos.y = FIELD_HEIGHT / 2 + BTN_HEIGHT + BTN_INDENT;
		}
		if (i == 2)
		{
			sscanf(END, "%s", buttons[i].name);
			buttons[i].centre_pos.y = FIELD_HEIGHT / 2 + BTN_HEIGHT + BTN_INDENT;
		}
	}
	return buttons;
}

void DrawMenu(Button* buttons, int btn_num) 
{
	HWND hWnd;
	HWND hTextFont;
	hWnd = FindWindow(NULL, L"Arcanoid");
	HDC hdc = GetWindowDC(hWnd);
	RECT r;
	GetWindowRect(hWnd, &r);

	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, r.right, r.bottom);

	SetTextColor(hdc, RGB(WHITE, WHITE, WHITE));
	SetBkColor(hdc, RGB(0, 0, 0));
	hTextFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, 0, 0, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, L"Lucida Console");
	SelectObject(hdc, hTextFont);
	if (btn_num != 1)
	{
		for (int i = 0; i < 3; i++)
		{
			ExtTextOutA(hdc, (buttons[i].centre_pos.x - BTN_WIDTH / 2 + BTN_WIDTH / strlen(buttons[i].name)), (buttons[i].centre_pos.y - BTN_HEIGHT / 2 + 10), NULL, &r, buttons[i].name, strlen(buttons[i].name), NULL);
		}
	}
	else
	{
		for (int i = 3; i < BTN_NUM; i++)
		{
			ExtTextOutA(hdc, (buttons[i].centre_pos.x - BTN_WIDTH / 2 + BTN_WIDTH / strlen(buttons[i].name)), (buttons[i].centre_pos.y - BTN_HEIGHT / 2 + 10), NULL, &r, buttons[i].name, strlen(buttons[i].name), NULL);
		}
	}
	
	DeleteObject(hTextFont);
	DeleteObject(hBrush);

}

void DrawBtn(HWND hWnd, Button* buttons, int btn_num, int last_btn)
{
	HDC hdc = GetWindowDC(hWnd);
	RECT r;
	GetWindowRect(hWnd, &r);
	HBRUSH hBrush;
	static HWND hTextFont;
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hPen;
	
	hTextFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, 0, 0, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, L"Lucida Console");
	SelectObject(hdc, hTextFont);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(WHITE, WHITE, WHITE));
	if (last_btn > -1)
	{
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		Rectangle(hdc, buttons[last_btn].centre_pos.x - BTN_WIDTH / 2, buttons[last_btn].centre_pos.y - BTN_HEIGHT / 2, buttons[last_btn].centre_pos.x + BTN_WIDTH / 2, buttons[last_btn].centre_pos.y + BTN_HEIGHT / 2);
		ExtTextOutA(hdc, (buttons[last_btn].centre_pos.x - BTN_WIDTH / 2 + BTN_WIDTH / strlen(buttons[last_btn].name)), (buttons[last_btn].centre_pos.y - BTN_HEIGHT / 2 + 10), NULL, &r, buttons[last_btn].name, strlen(buttons[last_btn].name), NULL);
	}
	hPen = CreatePen(PS_SOLID, 3, RGB(WHITE, WHITE, WHITE));
	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, buttons[btn_num].centre_pos.x - BTN_WIDTH / 2, buttons[btn_num].centre_pos.y - BTN_HEIGHT / 2, buttons[btn_num].centre_pos.x + BTN_WIDTH / 2, buttons[btn_num].centre_pos.y + BTN_HEIGHT / 2);
	ExtTextOutA(hdc, (buttons[btn_num].centre_pos.x - BTN_WIDTH / 2 + BTN_WIDTH / strlen(buttons[btn_num].name)), (buttons[btn_num].centre_pos.y - BTN_HEIGHT / 2 + 10), NULL, &r, buttons[btn_num].name, strlen(buttons[btn_num].name), NULL);
	DeleteObject(hPen);
	DeleteObject(hTextFont);
	DeleteObject(hBrush);
	ReleaseDC(hWnd, hdc);
}