#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Resource.h"
#include "framework.h"

#define GET 0
#define SET 1

#define WINDOW_X_POS 100
#define WINDOW_Y_POS 100
#define WINDOW_WIDTH 960

#define BORDER_WIDTH 4
#define WHITE 255

#define FIELD_HEIGHT 600
#define FIELD_WIDTH 480
#define UP_INDENT 70
#define RIGHT_INDENT 240

#define BRICK_HEIGHT 28
#define BRICK_WIDTH 60
#define FRAME 4

#define BALL_RAD 8
#define GRAY 85
#define BALL_SPEED 3

#define TIMER 1

#define RACKET_HEIGHT 15
#define RACKET_SIZE 50
#define RACKET_SPEED 20
#define START_HP 4
#define LINES 6

enum Bonus_Name
{
	HEALTHUP,
	STICKNESS
};

typedef struct
{
	int x;
	int y;
} point;

typedef struct
{
	point position;
	int name;
	int brick_num;
	int destroyed;
} Bonus;



typedef struct
{
	int r;
	int g;
	int b;
} rgb;

typedef struct
{
	int strength;
	point end_point;
	int color;
	int destroy;
	int bon;
} Brick;

typedef struct
{
	point centre;
	rgb color;
	int speed;
	int size;
	int hp;
} Racket;

typedef struct
{
	point position;
	point speed;
} Ball;


