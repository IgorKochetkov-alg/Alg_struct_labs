#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "Resource.h"
#include "framework.h"
#include <stdio.h>

#define CELL_SIZE 60
#define FIELD_SIZE 9

#define WINDOW_START_POS_X 300
#define WINDOW_START_POS_Y 40
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 700

#define BALL_RAD 20

typedef struct
{
	int x;
	int y;
} Position;

typedef struct
{ 
	int color;
	int ball;
	Position start_pos;
} Cell;

typedef struct
{
	int empty;
	int wave;
	int part_of_row;
	Position start_pos;
} Check;