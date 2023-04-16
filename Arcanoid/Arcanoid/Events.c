#include "Events.h"
#include "Game.h"

HWND hWnd;
HDC hdc;
RECT r;

int last_move;
int score;
Brick* bricks;
Ball* ball;
Racket* racket;
Bonus* bonuses;
int bonus_sum;
int destroyed_bricks;
int reflection_speed;

int touch_point;
int num;
int x_speed;
int y_speed;


void PickUpBonus()
{
	HWND hWnd = FindWindow(NULL, L"Arcanoid");
	HDC hdc = GetWindowDC(hWnd);
	char str[12] = { 0 };
	for (int i = 0; i < bonus_sum; i++)
	{
		if (bonuses[i].destroyed == 1)
		{
			if ((bonuses[i].position.x + BALL_RAD >= racket->centre.x - RACKET_SIZE) && (bonuses[i].position.x - BALL_RAD <= racket->centre.x + RACKET_SIZE) && (bonuses[i].position.y + BALL_RAD >= racket->centre.y - RACKET_HEIGHT))
			{
				DeleteBonuses(bonuses, bonus_sum);
				bonuses[i].destroyed = 0;
				switch (bonuses[i].name)
				{
				case HEALTHUP:
				{
					racket->hp += 1;
					SetTextColor(hdc, RGB(WHITE, WHITE, WHITE));
					SetBkColor(hdc, RGB(0, 0, 0));
					sprintf(str, "%c %d", 'x', racket->hp);
					ExtTextOutA(hdc, 9 * RIGHT_INDENT / 6 + FIELD_WIDTH, FIELD_HEIGHT * 3 / 4 + 60, NULL, &r, str, strlen(str), NULL);
				} break;

				case STICKNESS:
				{
					StartGameAtt(SET, 0);
					DeleteBall(ball);
					ball->position.x = racket->centre.x;
					ball->position.y = FIELD_HEIGHT - RACKET_HEIGHT - BALL_RAD;
					ball->speed.x = 0;
					ball->speed.y = 0;
					DrawBall(ball);

				} break;
				}
			}

		}

	}
}


void Update(int i)
{
	SetTextColor(hdc, RGB(WHITE, WHITE, WHITE));
	SetBkColor(hdc, RGB(0, 0, 0));
	char str[12] = { 0 };
	if (bricks[i].strength > 1)
	{
		bricks[i].strength -= 1;
	}
	else
	{
		bricks[i].destroy = 1;
		destroyed_bricks += 1;
		bricks[i].color = -1;
		score += 100 * destroyed_bricks;
		memset(str, 0, strlen(str));
		sprintf(str, "%d", score);
		ExtTextOutA(hdc, 17 * RIGHT_INDENT / 12 + FIELD_WIDTH, 80, NULL, &r, str, strlen(str), NULL);
		for (int j = 0; j < bonus_sum; j++)
		{
			if (i == bonuses[j].brick_num)
			{
				bonuses[j].destroyed = 1;
			}
		}
	}
	DrawBrick(bricks, i);
}

Brick TouchBrick()
{

	for (int i = 0; i < FIELD_WIDTH * LINES / BRICK_WIDTH; i++)
	{
		if (bricks[i].destroy == 0)
		{
			if ((sqrt((int)pow(ball->position.y + ball->speed.y - BALL_RAD - bricks[i].end_point.y, 2.0) <= BALL_RAD) && (ball->position.x + ball->speed.x >= bricks[i].end_point.x - BRICK_WIDTH) && (ball->position.x + ball->speed.x <= bricks[i].end_point.x)))
			{
				ball->speed.y = -ball->speed.y;
				Update(i);
				break;
			}
			if ((sqrt((int)pow(ball->position.y + ball->speed.y + BALL_RAD - bricks[i].end_point.y + BRICK_HEIGHT, 2.0) <= BALL_RAD) && (ball->position.x + ball->speed.x >= bricks[i].end_point.x - BRICK_WIDTH) && (ball->position.x + ball->speed.x <= bricks[i].end_point.x)))
			{
				ball->speed.y = -ball->speed.y;
				Update(i);

				break;
			}
			if ((sqrt((int)pow(ball->position.x + ball->speed.x + BALL_RAD - bricks[i].end_point.x + BRICK_WIDTH, 2.0)) <= BALL_RAD) && (ball->position.y + ball->speed.y >= bricks[i].end_point.y - BRICK_HEIGHT) && (ball->position.y + ball->speed.y <= bricks[i].end_point.y))
			{
				ball->speed.x = -ball->speed.x;
				Update(i);
				break;
			}
			if ((sqrt((int)pow(ball->position.x + ball->speed.x - BALL_RAD - bricks[i].end_point.x, 2.0)) <= BALL_RAD) && (ball->position.y + ball->speed.y >= bricks[i].end_point.y - BRICK_HEIGHT) && (ball->position.y + ball->speed.y <= bricks[i].end_point.y))
			{
				ball->speed.x = -ball->speed.x;
				Update(i);
				break;
			}
			/*if (((int)sqrt((int)pow(ball->position.x + ball->speed.x - bricks[i].end_point.x, 2.0) + (int)pow(ball->position.y + ball->speed.y - bricks[i].end_point.y, 2.0))) <= BALL_RAD)
			{
				ball->speed.x = -ball->speed.x;
				ball->speed.y = -ball->speed.y;
				Update(i);

				break;
			}
			if (((int)sqrt((int)pow(ball->position.x + ball->speed.x - bricks[i].end_point.x + BRICK_WIDTH, 2.0) + (int)pow(ball->position.y + ball->speed.y - bricks[i].end_point.y, 2.0))) <= BALL_RAD)
			{
				ball->speed.x = -ball->speed.x;
				ball->speed.y = -ball->speed.y;
				Update(i);
				break;
			}
			if (((int)sqrt((int)pow(ball->position.x + ball->speed.x - bricks[i].end_point.x + BRICK_WIDTH, 2.0) + (int)pow(ball->position.y + ball->speed.y - bricks[i].end_point.y + BRICK_HEIGHT, 2.0))) <= BALL_RAD)
			{
				ball->speed.x = -ball->speed.x;
				ball->speed.y = -ball->speed.y;
				Update(i);
				break;
			}
			if (((int)sqrt((int)pow(ball->position.x + ball->speed.x - bricks[i].end_point.x, 2.0) + (int)pow(ball->position.y + ball->speed.y - bricks[i].end_point.y + BRICK_HEIGHT, 2.0))) <= BALL_RAD)
			{
				ball->speed.x = -ball->speed.x;
				ball->speed.y = -ball->speed.y;
				Update(i);
				break;
			}*/

			if ((ball->position.x + ball->speed.x < bricks[i].end_point.x - BRICK_WIDTH) && (ball->position.y + ball->speed.y < bricks[i].end_point.y - BRICK_HEIGHT))
			{
				if (sqrt(pow(ball->position.x + ball->speed.x - bricks[i].end_point.x + BRICK_WIDTH, 2.0) + pow(ball->position.y + ball->speed.y - bricks[i].end_point.y + BRICK_HEIGHT, 2.0)) <= BALL_RAD)
				{
					x_speed = abs(ball->speed.x);
					y_speed = abs(ball->speed.y);
					ball->speed.x = -x_speed;
					ball->speed.y = -y_speed;
					Update(i);
					break;
				}
			}
			if ((ball->position.x + ball->speed.x < bricks[i].end_point.x - BRICK_WIDTH) && (ball->position.y + ball->speed.y > bricks[i].end_point.y))
			{
				if (sqrt(pow(ball->position.x + ball->speed.x - bricks[i].end_point.x + BRICK_WIDTH, 2.0) + pow(ball->position.y + ball->speed.y - bricks[i].end_point.y, 2.0)) <= BALL_RAD)
				{
					x_speed = abs(ball->speed.x);
					y_speed = abs(ball->speed.y);
					ball->speed.x = -x_speed;
					ball->speed.y = y_speed;
					Update(i);
					break;
				}
			}
			if ((ball->position.x + ball->speed.x > bricks[i].end_point.x) && (ball->position.y + ball->speed.y < bricks[i].end_point.y - BRICK_HEIGHT))
			{
				if (sqrt(pow(ball->position.x + ball->speed.x - bricks[i].end_point.x, 2.0) + pow(ball->position.y + ball->speed.y - bricks[i].end_point.y + BRICK_HEIGHT, 2.0)) <= BALL_RAD)
				{
					x_speed = abs(ball->speed.x);
					y_speed = abs(ball->speed.y);
					ball->speed.x = x_speed;
					ball->speed.y = -y_speed;
					Update(i);
					break;
				}
			}
			if ((ball->position.x + ball->speed.x > bricks[i].end_point.x) && (ball->position.y + ball->speed.y > bricks[i].end_point.y))
			{
				if (sqrt(pow(ball->position.x + ball->speed.x - bricks[i].end_point.x, 2.0) + pow(ball->position.y + ball->speed.y - bricks[i].end_point.y, 2.0)) <= BALL_RAD)
				{
					x_speed = abs(ball->speed.x);
					y_speed = abs(ball->speed.y);
					ball->speed.x = x_speed;
					ball->speed.y = y_speed;
					Update(i);
					break;
				}
			}
		}

	}
	/*for (int i = 0; i < LINES * FIELD_WIDTH / BRICK_WIDTH; i++)
	{
		if (bricks[i].destroy == 0)
		{
			if ((ball->position.x + ball->speed.x >= bricks[i].end_point.x - BRICK_WIDTH) && (ball->position.x + ball->speed.x <= bricks[i].end_point.x))
			{
				if ((ball->position.y + ball->speed.y - BALL_RAD <= bricks[i].end_point.y) && (ball->position.y + ball->speed.y - BALL_RAD > bricks[i].end_point.y - BRICK_HEIGHT))
				{
					touch_point = BOTTOM;
					num = i;
					break;
				}
				if ((ball->position.y + ball->speed.y + BALL_RAD >= bricks[i].end_point.y - BRICK_HEIGHT) && (ball->position.y + ball->speed.y + BALL_RAD < bricks[i].end_point.y))
				{
					touch_point = TOP;
					num = i;
					break;
				}
			}

			if ((ball->position.y + ball->speed.y >= bricks[i].end_point.y - BRICK_HEIGHT) && (ball->position.y + ball->speed.y <= bricks[i].end_point.y))
			{
				if ((ball->position.x + ball->speed.x - BALL_RAD <= bricks[i].end_point.x) && (ball->position.x + ball->speed.x - BALL_RAD > bricks[i].end_point.x - BRICK_WIDTH))
				{
					touch_point = RIGHT;
					num = i;
					break;
				}
				if ((ball->position.x + ball->speed.x + BALL_RAD >= bricks[i].end_point.x - BRICK_WIDTH) && (ball->position.x + ball->speed.x + BALL_RAD < bricks[i].end_point.x))
				{
					touch_point = LEFT;
					num = i;
					break;
				}
				break;
			}

			if ((ball->position.x + ball->speed.x < bricks[i].end_point.x - BRICK_WIDTH) && (ball->position.y + ball->speed.y < bricks[i].end_point.y - BRICK_HEIGHT))
			{
				if (sqrt(pow(ball->position.x + ball->speed.x - bricks[i].end_point.x + BRICK_WIDTH, 2.0) + pow(ball->position.y + ball->speed.y - bricks[i].end_point.y + BRICK_HEIGHT, 2.0)) <= BALL_RAD)
				{
					touch_point = LEFT_TOP_CORNER;
					num = i;
					break;
				}
			}
			if ((ball->position.x + ball->speed.x < bricks[i].end_point.x - BRICK_WIDTH) && (ball->position.y + ball->speed.y > bricks[i].end_point.y))
			{
				if (sqrt(pow(ball->position.x + ball->speed.x - bricks[i].end_point.x + BRICK_WIDTH, 2.0) + pow(ball->position.y + ball->speed.y - bricks[i].end_point.y, 2.0)) <= BALL_RAD)
				{
					touch_point = LEFT_BOTTOM_CORNER;
					num = i;
					break;
				}
			}
			if ((ball->position.x + ball->speed.x > bricks[i].end_point.x) && (ball->position.y + ball->speed.y < bricks[i].end_point.y - BRICK_HEIGHT))
			{
				if (sqrt(pow(ball->position.x + ball->speed.x - bricks[i].end_point.x, 2.0) + pow(ball->position.y + ball->speed.y - bricks[i].end_point.y + BRICK_HEIGHT, 2.0)) <= BALL_RAD)
				{
					touch_point = RIGHT_TOP_CORNER;
					num = i;
					break;
				}
			}
			if ((ball->position.x + ball->speed.x > bricks[i].end_point.x) && (ball->position.y + ball->speed.y > bricks[i].end_point.y))
			{
				if (sqrt(pow(ball->position.x + ball->speed.x - bricks[i].end_point.x, 2.0) + pow(ball->position.y + ball->speed.y - bricks[i].end_point.y, 2.0)) <= BALL_RAD)
				{
					touch_point = RIGHT_BOTTOM_CORNER;
					num = i;
					break;
				}
			}
		}
		if ((num != -1) && (touch_point != -1))
		{
			x_speed = abs(ball->speed.x);
			y_speed = abs(ball->speed.y);
			switch (touch_point)
			{
			case LEFT_TOP_CORNER:
			{
				ball->speed.x = -x_speed;
				ball->speed.y = -y_speed;
				Update(num);
			} break;
			case TOP:
			{
				ball->speed.y = -ball->speed.y;
				Update(num);
			} break;
			case RIGHT_TOP_CORNER:
			{
				ball->speed.x = x_speed;
				ball->speed.y = -y_speed;
				Update(num);
			} break;
			case RIGHT:
			{
				ball->speed.x = -ball->speed.x;
				Update(num);
			} break;
			case RIGHT_BOTTOM_CORNER:
			{
				ball->speed.x = x_speed;
				ball->speed.y = y_speed;
				Update(num);
			} break;
			case BOTTOM:
			{
				ball->speed.y = -ball->speed.y;
				Update(num);
			} break;
			case LEFT_BOTTOM_CORNER:
			{
				ball->speed.x = -x_speed;
				ball->speed.y = y_speed;
				Update(num);
			} break;
			case LEFT:
			{
				ball->speed.x = -ball->speed.x;
				Update(num);
			} break;
			}
			touch_point = -1;
			num = -1;
		}
	}*/
}

void MoveBall(Button* buttons)
{
	bricks = GetGameElement(GET_BRICKS);
	racket = GetGameElement(GET_RACKET);
	ball = GetGameElement(GET_BALL);
	bonuses = GetGameElement(GET_BONUSES);

	reflection_speed = ReflSpeedAtt(GET, NULL);
	last_move = LastMoveAtt(GET, NULL);
	destroyed_bricks = DstBricksAtt(GET, NULL);
	score = ScoreAtt(GET, NULL);
	bonus_sum = GetBonusSum();
	hWnd = FindWindow(NULL, L"Arcanoid");
	hdc = GetWindowDC(hWnd);

	if (last_move != 0)
	{
		if (last_move == 1)
		{
			ball->speed.x = BALL_SPEED;
			ball->speed.y = -BALL_SPEED;
			
			LastMoveAtt(SET, 0);
		} else
		{
			ball->speed.x = -BALL_SPEED;
			ball->speed.y = -BALL_SPEED;
			LastMoveAtt(SET, 0);
		}
		DeleteBall(ball);
		ball->position.x += ball->speed.x;
		ball->position.y += ball->speed.y;
		DrawBall(ball);
	}
	else
	{
		if (((ball->position.x + BALL_RAD + ball->speed.x) >= (RIGHT_INDENT + FIELD_WIDTH)) || ((ball->position.x - BALL_RAD + ball->speed.x) <= RIGHT_INDENT))
		{
			ball->speed.x = -ball->speed.x;
			DrawBorder();
		} //отталкивание от стен
		if ((ball->position.y + ball->speed.y - BALL_RAD - 31 <= 0) && (ball->position.x + ball->speed.x - BALL_RAD >= RIGHT_INDENT + BORDER_WIDTH))
		{
			ball->speed.y = -ball->speed.y;
		} //отталкивание от потолка     

		if ((sqrt((int)pow(ball->position.y + ball->speed.y - racket->centre.y + RACKET_HEIGHT, 2.0) <= BALL_RAD) && (ball->position.x + ball->speed.x >= racket->centre.x - RACKET_SIZE) && (ball->position.x + ball->speed.x <= racket->centre.x + RACKET_SIZE)))
		{
			ball->speed.x = ball->speed.x + reflection_speed / 6;
			ball->speed.y = -ball->speed.y;
		}
		else
		{
			if (((int)sqrt((int)pow(ball->position.x + ball->speed.x - racket->centre.x + RACKET_SIZE, 2.0) + (int)pow(ball->position.y + ball->speed.y - racket->centre.y + RACKET_HEIGHT, 2.0))) <= BALL_RAD)
			{
				if (ball->speed.x > 0)
				{
					ball->speed.x = -ball->speed.x;
					ball->speed.y = -ball->speed.y;
				}

			}
			if (((int)sqrt((int)pow(ball->position.x + ball->speed.x - racket->centre.x - RACKET_SIZE, 2.0) + (int)pow(ball->position.y + ball->speed.y - racket->centre.y + RACKET_HEIGHT, 2.0))) <= BALL_RAD)
			{
				if (ball->speed.x < 0)
				{
					ball->speed.x = -ball->speed.x;
					ball->speed.y = -ball->speed.y;
				}
			}
		}
		
	}
	
	TouchBrick();
	PickUpBonus();

	EndGame(buttons);
	DrawBonuses(bonuses, bonus_sum);

	DeleteBall(ball);
	ball->position.x += ball->speed.x;
	ball->position.y += ball->speed.y;
	DrawBall(ball);

	ReflSpeedAtt(SET, reflection_speed);
	DstBricksAtt(SET, destroyed_bricks);
	ScoreAtt(SET, score);


	ReleaseDC(hWnd, hdc);
	SetBall(ball);
	SetBonuses(bonuses);
}



