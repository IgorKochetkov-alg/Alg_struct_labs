#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "Arcanoid.h"


void DrawBorder();

void DrawBrick(Brick* bricks, int num);

void DrawRacket(Racket* racket);

void DrawBall(Ball* ball);

void DeleteBall(Ball* ball);

void DeleteRacket(Racket* racket);

void DrawBonuses(Bonus* bonuses, int bonus_sum);

void DeleteBonuses(Bonus* bonuses, int bonus_sum);