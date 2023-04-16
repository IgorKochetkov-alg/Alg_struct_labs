#include "DrawFunctions.h"
HWND hWnd;
HDC hdc;
RECT* r;

void DrawInit()
{
	hWnd = FindWindow(NULL, L"Arcanoid");
	hdc = GetWindowDC(hWnd);
}

void DrawRelease()
{
	ReleaseDC(hWnd, hdc);
}

void DrawBorder()
{
	DrawInit();
	HPEN hPen = CreatePen(PS_SOLID, 2 * BORDER_WIDTH, RGB(WHITE, WHITE, WHITE));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, RIGHT_INDENT - BORDER_WIDTH, 0, NULL);
	LineTo(hdc, RIGHT_INDENT - BORDER_WIDTH, FIELD_HEIGHT);
	MoveToEx(hdc, RIGHT_INDENT + BORDER_WIDTH + FIELD_WIDTH, 0, NULL);
	LineTo(hdc, RIGHT_INDENT + BORDER_WIDTH + FIELD_WIDTH, FIELD_HEIGHT);
	MoveToEx(hdc, RIGHT_INDENT + BORDER_WIDTH + FIELD_WIDTH, FIELD_HEIGHT / 4, NULL);
	LineTo(hdc, RIGHT_INDENT + BORDER_WIDTH + FIELD_WIDTH + RIGHT_INDENT, FIELD_HEIGHT / 4);
	MoveToEx(hdc, RIGHT_INDENT + BORDER_WIDTH + FIELD_WIDTH, FIELD_HEIGHT * 3/ 4, NULL);
	LineTo(hdc, RIGHT_INDENT + BORDER_WIDTH + FIELD_WIDTH + RIGHT_INDENT, FIELD_HEIGHT * 3/ 4);
	SetTextColor(hdc, RGB(WHITE, WHITE, WHITE));
	SetBkColor(hdc, RGB(0, 0, 0));
	ExtTextOutA(hdc,17 *RIGHT_INDENT / 12 + FIELD_WIDTH, 50, NULL, r, "SCORE:", 6, NULL);
	ExtTextOutA(hdc, 9 * RIGHT_INDENT / 6 + FIELD_WIDTH, FIELD_HEIGHT * 3 / 4 + 30, NULL, r, "HP:", 3, NULL);
	DeleteObject(hPen);
	DrawRelease();
}

void DrawBrick(Brick* bricks, int i)
{
	static HBRUSH hBrush;
	static HBRUSH hBrush1;
	static HPEN hPen;
	static HPEN hPen1;

	DrawInit();

	switch (bricks[i].color)
	{
	case -1:
	{
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hPen = CreatePen(PS_SOLID, FRAME + 1, RGB(0, 0, 0));
	} break;
	case 0:
	{
		hBrush = CreateSolidBrush(RGB(0, 45, 255));
		hPen = CreatePen(PS_SOLID, FRAME + 1, RGB(0, 175, 255));
		hBrush1 = CreateSolidBrush(RGB(0, 175, 255));
		hPen1 = CreatePen(PS_SOLID, 2, RGB(0, 175, 255));

	} break;
	case 1:
	{
		hBrush = CreateSolidBrush(RGB(50, 160, 10));
		hPen = CreatePen(PS_SOLID, FRAME + 1, RGB(50, 255, 25));
		hBrush1 = CreateSolidBrush(RGB(50, 255, 25));
		hPen1 = CreatePen(PS_SOLID, 2, RGB(50, 255, 25));
		
	} break;
	case 2:
	{
		hBrush = CreateSolidBrush(RGB(180, 35, 180));
		hPen = CreatePen(PS_SOLID, FRAME + 1, RGB(250, 55, 250));
		hBrush1 = CreateSolidBrush(RGB(250, 55, 250));
		hPen1 = CreatePen(PS_SOLID, 2, RGB(250, 55, 250));


	} break;
	case 3:
	{
		hBrush = CreateSolidBrush(RGB(155, 5, 5));
		hPen = CreatePen(PS_SOLID, FRAME + 1, RGB(255, 55, 55));
		hBrush1 = CreateSolidBrush(RGB(255, 55, 55));
		hPen1 = CreatePen(PS_SOLID, 2, RGB(255, 55, 55));


	} break;
	case 4:
	{
		hBrush = CreateSolidBrush(RGB(255, 140, 5));
		hPen = CreatePen(PS_SOLID, FRAME + 1, RGB(255, 170, 45));
		hBrush1 = CreateSolidBrush(RGB(255, 170, 45));
		hPen1 = CreatePen(PS_SOLID, 2, RGB(255, 170, 45));

	} break;
	}

	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, bricks[i].end_point.x - BRICK_WIDTH + FRAME / 2, bricks[i].end_point.y - BRICK_HEIGHT + FRAME / 2, bricks[i].end_point.x - FRAME / 2, bricks[i].end_point.y - FRAME / 2);
	if (bricks[i].strength > 1)
	{
		if (bricks[i].strength > 2)
		{
			SelectObject(hdc, hPen1);
			Rectangle(hdc, bricks[i].end_point.x - BRICK_WIDTH + 7, bricks[i].end_point.y - BRICK_HEIGHT + 7, bricks[i].end_point.x - 6, bricks[i].end_point.y - 6);
			SelectObject(hdc, hBrush1);
			Rectangle(hdc, bricks[i].end_point.x - BRICK_WIDTH + 10, bricks[i].end_point.y - BRICK_HEIGHT + 10, bricks[i].end_point.x - 9, bricks[i].end_point.y - 9);

		}
		else
		{
			SelectObject(hdc, hPen1);
			Rectangle(hdc, bricks[i].end_point.x - BRICK_WIDTH + 7, bricks[i].end_point.y - BRICK_HEIGHT + 7, bricks[i].end_point.x - 6, bricks[i].end_point.y - 6);
		}
	}
	DeleteObject(hBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush1);
	DeleteObject(hPen1);
	DrawRelease();
}

void DrawRacket(Racket* racket)
{
	DrawInit();
	HPEN hPen = CreatePen(BS_SOLID, 0, RGB(racket->color.r, racket->color.g, racket->color.b));
	HBRUSH hBrush = CreateSolidBrush(RGB(racket->color.r, racket->color.g, racket->color.b));
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);
	Rectangle(hdc, racket->centre.x - RACKET_SIZE, racket->centre.y - RACKET_HEIGHT / 2, racket->centre.x + RACKET_SIZE, racket->centre.y + RACKET_HEIGHT / 2);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	DrawRelease();
}

void DrawBall(Ball* ball)
{
	DrawInit();
	HBRUSH hBrush = CreateSolidBrush(RGB(GRAY, GRAY, GRAY));
	SelectObject(hdc, hBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(GRAY, GRAY, GRAY));
	SelectObject(hdc, hPen);
	Ellipse(hdc, ball->position.x - BALL_RAD, ball->position.y - BALL_RAD, ball->position.x + BALL_RAD, ball->position.y + BALL_RAD);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	DrawRelease();
}

void DeleteBall(Ball* ball)
{
	DrawInit();
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	Ellipse(hdc, ball->position.x - BALL_RAD, ball->position.y - BALL_RAD, ball->position.x + BALL_RAD, ball->position.y + BALL_RAD);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	DrawRelease();
}

void DeleteRacket(Racket* racket)
{
	DrawInit();
	HPEN hPen = CreatePen(BS_SOLID, 0, RGB(0, 0, 0));
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, racket->centre.x - RACKET_SIZE, racket->centre.y - RACKET_HEIGHT / 2, racket->centre.x + RACKET_SIZE, racket->centre.y + RACKET_HEIGHT / 2);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	DrawRelease();
}

void DrawBonuses(Bonus* bonuses, int bonus_sum)
{
	DrawInit();
	for (int i = 0; i < bonus_sum; i++)
	{
		if (bonuses[i].destroyed == 1)
		{

			HPEN hPen;
			hPen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
			SelectObject(hdc, hPen);
			HBRUSH hBrush;
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, bonuses[i].position.x - BALL_RAD, bonuses[i].position.y - BALL_RAD, bonuses[i].position.x + BALL_RAD, bonuses[i].position.y + BALL_RAD);
			DeleteObject(hBrush);
			if (bonuses[i].position.y - BALL_RAD < FIELD_HEIGHT)
			{
				bonuses[i].position.y += BALL_SPEED / 2;
				switch (bonuses[i].name)
				{
				case HEALTHUP:
				{
					HBRUSH hBrush1;
					hBrush1 = CreateSolidBrush(RGB(255, 0, 0));
					
					SelectObject(hdc, hBrush1);
					Ellipse(hdc, bonuses[i].position.x - BALL_RAD, bonuses[i].position.y - BALL_RAD, bonuses[i].position.x + BALL_RAD, bonuses[i].position.y + BALL_RAD);
					DeleteObject(hBrush1);
				} break;
				
				case STICKNESS:
				{
					HBRUSH hBrush1;
					hBrush1 = CreateSolidBrush(RGB(255, 230, 0));
					SelectObject(hdc, hBrush1);
					Ellipse(hdc, bonuses[i].position.x - BALL_RAD, bonuses[i].position.y - BALL_RAD, bonuses[i].position.x + BALL_RAD, bonuses[i].position.y + BALL_RAD);
					DeleteObject(hBrush1);
				} break;
			} 
					
				DeleteObject(hPen);
			}
			
		}
	}
	DrawRelease();
}

void DeleteBonuses(Bonus* bonuses, int bonus_sum)
{
	DrawInit();
	for (int i = 0; i < bonus_sum; i++)
	{
		if (bonuses[i].destroyed == 1)
		{

			HPEN hPen;
			hPen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
			SelectObject(hdc, hPen);
			HBRUSH hBrush;
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, bonuses[i].position.x - BALL_RAD, bonuses[i].position.y - BALL_RAD, bonuses[i].position.x + BALL_RAD, bonuses[i].position.y + BALL_RAD);
			DeleteObject(hBrush);
			DeleteObject(hPen);
		}
	}
	DrawRelease();
}
