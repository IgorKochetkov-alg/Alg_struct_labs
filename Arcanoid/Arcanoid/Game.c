#include "DrawFunctions.h"
#include "Menu.h"
#include "Game.h"



Brick* bricks = NULL;
Ball* ball = NULL;
Racket* racket = NULL;
Bonus* bonuses = NULL;


int level = 0;
int bonus_sum = 0;
int score = 0;
int destroyed_bricks = 0;
int last_move = 0;
int difficulty = 1;
int reflection_speed = 0;
int start_game = 0;




Bonus* NewLevel()
{
	if (racket == NULL)
	{
		racket = (Racket*)calloc(1, sizeof(Racket));
	}
	if (ball == NULL)
	{
		ball = (Ball*)calloc(1, sizeof(Ball));
	}
	HWND hWnd;
	level++;
	bricks = (Brick*)realloc(bricks, (FIELD_WIDTH * LINES / BRICK_WIDTH) * sizeof(Brick));
	racket->centre.x = FIELD_WIDTH / 2 + RIGHT_INDENT;
	racket->centre.y = FIELD_HEIGHT - RACKET_HEIGHT / 2;
	srand(time(NULL));
	racket->color.r = rand() % 255;
	racket->color.g = rand() % 255;
	racket->color.b = rand() % 255;
	racket->speed = RACKET_SPEED;
	if (racket->hp == 0)
	{
		racket->hp = START_HP;
	}
	ball->position.x = FIELD_WIDTH / 2 + RIGHT_INDENT;
	ball->position.y = FIELD_HEIGHT - RACKET_HEIGHT - BALL_RAD;
	ball->speed.x = 0;
	ball->speed.y = 0;
	char str[12] = { 0 };

	hWnd = FindWindow(NULL, L"Arcanoid");

	HDC hdc = GetWindowDC(hWnd);
	RECT r;
	GetWindowRect(hWnd, &r);
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, r.right, r.bottom);
	DrawBorder();

	for (int i = 0; i < FIELD_WIDTH * LINES / BRICK_WIDTH; i++)
	{
		bricks[i].end_point.x = BRICK_WIDTH * (i / LINES) + RIGHT_INDENT + BRICK_WIDTH;
		bricks[i].end_point.y = UP_INDENT + BRICK_HEIGHT + (i % LINES) * BRICK_HEIGHT;

		bricks[i].color = rand() % 5;
		if (difficulty == 1)
		{
			bricks[i].strength = rand() % 2 + 1;
		}
		if (difficulty == 2)
		{
			bricks[i].strength = rand() % 3 + 1;
		}
		if (difficulty == 3)
		{
			bricks[i].strength = rand() % 2 + 2;
		}
		bricks[i].destroy = 0;
		bricks[i].bon = rand() % 4;
		if (bricks[i].bon == 0)
		{
			bricks[i].bon = rand() % 4;
			bonus_sum++;
			bonuses = (Bonus*)realloc(bonuses, bonus_sum * sizeof(Bonus));
			bonuses[bonus_sum - 1].position.x = bricks[i].end_point.x - BRICK_WIDTH / 2;
			bonuses[bonus_sum - 1].position.y = bricks[i].end_point.y - BRICK_HEIGHT / 2;
			bonuses[bonus_sum - 1].brick_num = i;
			bonuses[bonus_sum - 1].name = bricks[i].bon;
			bonuses[bonus_sum - 1].destroyed = 0;
		}
		else
		{
			bricks[i].bon = 0;
		}
		DrawBrick(bricks, i);
	}
	DrawRacket(racket);
	DrawBall(ball);

	SetTextColor(hdc, RGB(WHITE, WHITE, WHITE));
	SetBkColor(hdc, RGB(0, 0, 0));
	memset(str, 0, strlen(str));
	sprintf(str, "%c %d", 'x', racket->hp);
	ExtTextOutA(hdc, 9 * RIGHT_INDENT / 6 + FIELD_WIDTH, FIELD_HEIGHT * 3 / 4 + 60, NULL, &r, str, strlen(str), NULL);
	memset(str, 0, strlen(str));
	sprintf(str, "%d", score);
	ExtTextOutA(hdc, 17 * RIGHT_INDENT / 12 + FIELD_WIDTH, 80, NULL, &r, str, strlen(str), NULL);
	DeleteObject(hBrush);
	ReleaseDC(hWnd, hdc);
	return bonuses;
}

void EndGame(Button* buttons)
{

	HWND hWnd;
	hWnd = FindWindow(NULL, L"Arcanoid");
	HDC hdc = GetWindowDC(hWnd);
	RECT r;
	GetWindowRect(hWnd, &r);
	char str[12] = { 0 };

	if (ball->position.y + BALL_RAD + ball->speed.y >= FIELD_HEIGHT)
	{
		DeleteBall(ball);
		DeleteRacket(racket);
		if (racket->hp - 1 > 0)
		{
			racket->centre.x = FIELD_WIDTH / 2 + RIGHT_INDENT;
			racket->centre.y = FIELD_HEIGHT - RACKET_HEIGHT / 2;
			ball->position.x = FIELD_WIDTH / 2 + RIGHT_INDENT;
			ball->position.y = FIELD_HEIGHT - RACKET_HEIGHT - BALL_RAD;
			ball->speed.x = 0;
			ball->speed.y = 0;
			DrawRacket(racket);
			DrawBall(ball);
			racket->hp -= 1;
			start_game = 0;
			SetTextColor(hdc, RGB(WHITE, WHITE, WHITE));
			SetBkColor(hdc, RGB(0, 0, 0));
			sprintf(str, "%c %d", 'x', racket->hp);
			ExtTextOutA(hdc, 9 * RIGHT_INDENT / 6 + FIELD_WIDTH, FIELD_HEIGHT * 3 / 4 + 60, NULL, &r, str, strlen(str), NULL);
		}
		else
		{
			HBRUSH hBrush;
			GetWindowRect(hWnd, &r);
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, 0, 0, r.right, r.bottom);
			DeleteObject(hBrush);
			KillTimer(hWnd, TIMER);
			start_game = 0;
			racket->hp = 0;
			score = 0;
			DrawMenu(buttons, 0);
			memset(bonuses, 0, bonus_sum * sizeof(Bonus));
			memset(bricks, 0, (LINES * FIELD_WIDTH / BRICK_WIDTH) * sizeof(Brick));

		}
	} //промах


	if (destroyed_bricks == LINES * FIELD_WIDTH / BRICK_WIDTH)
	{
		bonuses = NewLevel();
		KillTimer(hWnd, TIMER);
		start_game = 0;
		destroyed_bricks = 0;
		DeleteRacket(racket);
		memset(bonuses, 0, bonus_sum * sizeof(Bonus));
		memset(bricks, 0, (LINES * FIELD_WIDTH / BRICK_WIDTH) * sizeof(Brick));
	}

	if (level > 3)
	{
		HWND hTextFont;
		HBRUSH hBrush;
		KillTimer(hWnd, TIMER);
		start_game = 0;
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		memset(bonuses, 0, bonus_sum * sizeof(Bonus));
		memset(bricks, 0, (LINES * FIELD_WIDTH / BRICK_WIDTH) * sizeof(Brick));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 0, 0, r.right, r.bottom);
		level = 0;
		SetTextColor(hdc, RGB(WHITE, WHITE, WHITE));
		SetBkColor(hdc, RGB(0, 0, 0));
		hTextFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, 0, 0, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH, L"Lucida Console");
		SelectObject(hdc, hTextFont);
		ExtTextOutA(hdc, WINDOW_WIDTH / 2 - 30, FIELD_HEIGHT / 2 - 10, NULL, &r, "YOU WIN!!!", 10, NULL);
		DeleteObject(hBrush);
		DeleteObject(hTextFont);
	}

	if (ball->position.y + ball->speed.y - BALL_RAD - 31 <= 0)
	{
		if (ball->position.x < RIGHT_INDENT - BORDER_WIDTH)
		{
			start_game = 0;
			DeleteBall(ball);
			DeleteRacket(racket);
			memset(bonuses, 0, bonus_sum * sizeof(Bonus));
			memset(bricks, 0, (LINES * FIELD_WIDTH / BRICK_WIDTH) * sizeof(Brick));
			bonuses = NewLevel();
		}
	}    
	ReleaseDC(hWnd, hdc);
}



void SetDiff(int diff)
{
	difficulty = diff;
	return;
}

int ReflSpeedAtt(int mode, int speed)
{
	switch (mode)
	{
	case GET:
	{
		return reflection_speed;
	} break;
	case SET:
	{
		reflection_speed = speed;
		return;
	} break;
	}
}

int GetBonusSum()
{
	return bonus_sum;
}

int ScoreAtt(int mode, int sum)
{
	switch (mode)
	{
	case GET:
	{
		return score;
	} break;

	case SET:
	{
		score = sum;
		return;
	} break;
	}
}

int StartGameAtt(int mode, int game_start)
{
	switch (mode)
	{
	case GET:
	{
		return start_game;
	} break;

	case SET:
	{
		start_game = game_start;
		return;
	} break;
	}
}

void* GetGameElement(int el)
{

	switch (el)
	{
	case GET_BRICKS:
	{
		return bricks;
	} break;
	case GET_RACKET:
	{
		return racket;
	} break;
	case GET_BALL:
	{
		return ball;
	} break;
	case GET_BONUSES:
	{
		return bonuses;
	} break;
	}
}

void SetBonuses(Bonus* old_bonuses)
{
	bonuses = old_bonuses;
}

void SetBall(Ball* old_ball)
{
	ball = old_ball;
}

void SetRacket(Racket* old_racket)
{
	racket = old_racket;
}

int DstBricksAtt(int mode, int dst_bricks)
{
	switch (mode)
	{
	case GET:
	{
		return destroyed_bricks;
	} break;

	case SET:
	{
		destroyed_bricks = dst_bricks;
		return;
	} break;
	}
}

int LastMoveAtt(int mode, int move)
{
	switch (mode)
	{
	case GET:
	{
		return last_move;
	} break;
	case SET:
	{
		last_move = move;
		return;
	} break;
	}
}