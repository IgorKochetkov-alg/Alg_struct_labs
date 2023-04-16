#include "Functions.h"


void DrawCell(int x_pos, int y_pos)
{
	HWND hWnd = FindWindow(NULL, L"Lines");
	HDC hdc = GetDC(hWnd);
	RECT r;
	GetClientRect(hWnd, &r);

	HBRUSH hBrush = CreateSolidBrush(RGB(200, 200, 200));
	HPEN hPen = CreatePen(BS_SOLID, 2, RGB(150, 150, 150));
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);

	Rectangle(hdc, x_pos, y_pos, x_pos + CELL_SIZE, y_pos + CELL_SIZE);
	
	DeleteObject(hBrush);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void DrawBall(int x_pos, int y_pos, int color)
{
	HWND hWnd = FindWindow(NULL, L"Lines");
	HDC hdc = GetDC(hWnd);
	static HBRUSH hBrush;
	static HPEN hPen;

	if (color == RED)
	{
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		hPen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
	}
	if (color == GREEN)
	{
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		hPen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
	}
	if (color == BLUE)
	{
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		hPen = CreatePen(BS_SOLID, 2, RGB(0, 0, 255));
	}
	 
	 
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);

	Ellipse(hdc, x_pos + CELL_SIZE / 2 - BALL_RAD, y_pos + CELL_SIZE / 2 - BALL_RAD, x_pos + CELL_SIZE / 2 + BALL_RAD, y_pos + CELL_SIZE / 2 + BALL_RAD);
	
	DeleteObject(hBrush);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}