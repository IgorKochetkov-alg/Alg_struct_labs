#include "Functions.h"
#include <time.h>

Position start_cell;
Position finish_cell;

int ball_sum = 0;
int check = 0;
int find_row = 0;
int score = 0;

Cell cells[FIELD_SIZE][FIELD_SIZE];
Check check_cells[FIELD_SIZE][FIELD_SIZE];


void PrintNumber()
{
	HWND hWnd;
	hWnd = FindWindow(NULL, L"Lines");
	HDC hdc = GetDC(hWnd);
	RECT r = {10, 10, 30, 20};
	wchar_t buff[10] = {0};
	swprintf(buff, 3, L"%d", ball_sum);
	ExtTextOutA(hdc, 10, 10, NULL, &r, buff, 12, NULL);
	ReleaseDC(hWnd, hdc);
}

void PrintScore()
{
	HWND hWnd;
	hWnd = FindWindow(NULL, L"Lines");
	HDC hdc = GetDC(hWnd);
	RECT r;
	GetClientRect(hWnd, &r);
	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	ExtTextOutA(hdc, r.right - 150, 10, NULL, &r, "SCORE:", 6, NULL);
	wchar_t buff[10] = { 0 };
	swprintf(buff, 8, L"%d", score);
	ExtTextOutA(hdc, r.right - 90, 10, NULL, &r, buff, 8, NULL);
	ReleaseDC(hWnd, hdc);
}

void EndGame()
{
	HWND hWnd;
	hWnd = FindWindow(NULL, L"Lines");
	HDC hdc = GetDC(hWnd);
	RECT r;
	GetClientRect(hWnd, &r);
	HWND hTextFont;
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	HPEN hPen = CreatePen(BS_SOLID, 2, RGB(255, 255, 255));

	ball_sum = 0;
	score = 0;

	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);
	Rectangle(hdc, 0, 0, r.right, r.bottom);
	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	hTextFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, 0, 0, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, L"Lucida Console");
	SelectObject(hdc, hTextFont);
	ExtTextOutA(hdc, r.right / 2 - r.right / 24, r.bottom / 2, NULL, &r, "Game Over!!!", 12, NULL);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	DeleteObject(hTextFont);
	ReleaseDC(hWnd, hdc);
}

void NewBalls()
{
	int ball_num = 0;
	int vertical = -1;
	int horizontal = -1;
	int max_ball = 3;

	if (ball_sum + 2 == FIELD_SIZE * FIELD_SIZE)
	{
		max_ball = 2;
	}
	if (ball_sum + 1 == FIELD_SIZE * FIELD_SIZE)
	{
		max_ball = 1;
	}

	while (ball_num < max_ball)
	{
		horizontal = rand() % FIELD_SIZE;
		vertical = rand() % FIELD_SIZE;
		if (cells[horizontal][vertical].ball == 0)
		{
			cells[horizontal][vertical].ball = 1;
			cells[horizontal][vertical].color = rand() % 3 + 1;
			DrawBall(cells[horizontal][vertical].start_pos.x, cells[horizontal][vertical].start_pos.y, cells[horizontal][vertical].color);
			ball_num = ball_num + 1;
			ball_sum = ball_sum + 1;
		}
	}
}

void FieldInit()
{
	srand(time(NULL));
	HWND hWnd = FindWindow(NULL, L"Lines");
	RECT r;
	GetClientRect(hWnd, &r);
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			cells[i][j].start_pos.x = (r.right / 2) + (j - (FIELD_SIZE / 2)) * CELL_SIZE - CELL_SIZE / 2;
			cells[i][j].start_pos.y = (r.bottom / 2) + (i - (FIELD_SIZE / 2)) * CELL_SIZE - CELL_SIZE / 2;
			DrawCell(cells[i][j].start_pos.x, cells[i][j].start_pos.y);
			cells[i][j].ball = 0;
		}
	}
	NewBalls();
	PrintNumber();
	PrintScore();
}

void CheckRows(int parameter)
{
	int row = -1;
	int col = -1;
	int prev_color = 0;;
	int counter = 0;

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if ((row == -1) && (col == -1) && (cells[i][j].ball == 1))
			{
				row = i;
				col = j;
				prev_color = cells[i][j].color;
				counter = 1;
			}
			else
			{
				if ((row != -1) && (col != -1))
				{
					if ((cells[i][j].color == prev_color) && (j - col == counter))
					{
						counter++;
						if ((j == FIELD_SIZE - 1) && (counter >= 5))
						{
							for (int k = 0; k < counter; k++)
							{
								check_cells[row][col + k].part_of_row = 1;
							}
						}
					}
					else
					{
						if (counter >= 5)
						{
							for (int k = 0; k < counter; k++)
							{
								check_cells[row][col + k].part_of_row = 1;
							}
						}
						if (cells[i][j].ball == 1)
						{
							row = i;
							col = j;
							prev_color = cells[i][j].color;
							counter = 1;
						}
						else
						{
							counter = 0;
							prev_color = 0;
							row = -1;
							col = -1;
						}
					}	
				}
			}
		}
		counter = 0;
		prev_color = 0;
		row = -1;
		col = -1;
	}

	for (int j = 0; j < FIELD_SIZE; j++)
	{
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			if ((row == -1) && (col == -1) && (cells[i][j].ball == 1))
			{
				row = i;
				col = j;
				prev_color = cells[i][j].color;
				counter = 1;
			}
			else
			{
				if ((row != -1) && (col != -1))
				{
					if ((cells[i][j].color == prev_color) && (i - row == counter))
					{
						counter++;
						if ((i == FIELD_SIZE - 1) && (counter >= 5))
						{
							for (int k = 0; k < counter; k++)
							{
								check_cells[row + k][col].part_of_row = 1;
							}
						}
					}
					else
					{
						if (counter >= 5)
						{
							for (int k = 0; k < counter; k++)
							{
								check_cells[row + k][col].part_of_row = 1;
							}
						}
						if (cells[i][j].ball == 1)
						{
							row = i;
							col = j;
							prev_color = cells[i][j].color;
							counter = 1;
						}
						else
						{
							counter = 0;
							prev_color = 0;
							row = -1;
							col = -1;
						}
					}
				}
			}
		}
		counter = 0;
		prev_color = 0;
		row = -1;
		col = -1;
	}

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (check_cells[i][j].part_of_row == 1)
			{
				counter++;
				find_row = 1;
				cells[i][j].ball = 0;
				check_cells[i][j].part_of_row = 0;
				cells[i][j].color = 0;
				DrawCell(cells[i][j].start_pos.x, cells[i][j].start_pos.y);
			}
		}
	}

	ball_sum = ball_sum - counter;
	score = score + counter * parameter;
	PrintScore();
	PrintNumber();
}

void RollBall(int x, int y)
{
	int checked_cells = 0;
	int curr_wave = 0;
	int last_check = -1;

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			check_cells[i][j].wave = -1;
			check_cells[i][j].part_of_row = 0;
			if ((x > cells[i][j].start_pos.x) && (x < cells[i][j].start_pos.x + CELL_SIZE) && (y > cells[i][j].start_pos.y) && (y < cells[i][j].start_pos.y + CELL_SIZE))
			{
				if (cells[i][j].ball)
				{
					start_cell.x = i;
					start_cell.y = j;
					check = 1;
					break;
				}
				else
				{
					if (check == 1)
					{
						finish_cell.x = i;
						finish_cell.y = j;
						check = 2;
						break;
					}
				}
			}
		}
	}


	if (check == 2)
	{
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				if (cells[i][j].ball == 1)
				{
					check_cells[i][j].empty = 0;
				}
				else
				{
					check_cells[i][j].empty = 1;
				}
			}
		}
		check_cells[start_cell.x][start_cell.y].wave = 0;

		while (last_check != checked_cells)
		{
			curr_wave = curr_wave + 1;
			last_check = checked_cells;
			for (int i = 0; i < FIELD_SIZE; i++)
			{
				for (int j = 0; j < FIELD_SIZE; j++)
				{
					if (check_cells[i][j].wave == (curr_wave - 1))
					{
						if (i - 1 >= 0)
						{
							if ((check_cells[i - 1][j].wave == -1) && (check_cells[i - 1][j].empty == 1))
							{
								check_cells[i - 1][j].wave = curr_wave;
								checked_cells = checked_cells + 1;
							}
						}
					
						if (j - 1 >= 0)
						{
							if ((check_cells[i][j - 1].wave == -1) && (check_cells[i][j - 1].empty == 1))
							{
								check_cells[i][j - 1].wave = curr_wave;
								checked_cells = checked_cells + 1;
							}
						}

						if (i + 1 < FIELD_SIZE)
						{
							if ((check_cells[i + 1][j].wave == -1) && (check_cells[i + 1][j].empty == 1))
							{
								check_cells[i + 1][j].wave = curr_wave;
								checked_cells = checked_cells + 1;
							}
						}

						if (j + 1 < FIELD_SIZE)
						{
							if ((check_cells[i][j + 1].wave == -1) && (check_cells[i][j + 1].empty == 1))
							{
								check_cells[i][j + 1].wave = curr_wave;
								checked_cells = checked_cells + 1;
							}
						}
						
					}
				}
			}
		}
		if (check_cells[finish_cell.x][finish_cell.y].wave >= 0)
		{
			DrawBall(cells[finish_cell.x][finish_cell.y].start_pos.x, cells[finish_cell.x][finish_cell.y].start_pos.y, cells[start_cell.x][start_cell.y].color);
			DrawCell(cells[start_cell.x][start_cell.y].start_pos.x, cells[start_cell.x][start_cell.y].start_pos.y);
			cells[finish_cell.x][finish_cell.y].ball = 1;
			cells[start_cell.x][start_cell.y].ball = 0;
			cells[finish_cell.x][finish_cell.y].color = cells[start_cell.x][start_cell.y].color;
			cells[start_cell.x][start_cell.y].color = 0;
			check = 0;
			CheckRows(USER);
			if (ball_sum < FIELD_SIZE * FIELD_SIZE)
			{
				if (find_row != 1)
				{
					NewBalls();
					CheckRows(PROGRAM);
					if (ball_sum >= (FIELD_SIZE * FIELD_SIZE))
					{
						EndGame();
					}
				}
			}
			find_row = 0;
		}
	}
}