#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "Arcanoid.h"

#define GET_BRICKS 0
#define GET_RACKET 1
#define GET_BALL 2
#define GET_BONUSES 3
#define GET_BUTTONS 4



Bonus* NewLevel();

void EndGame(Button* buttons);


void SetDiff(int diff);

int ReflSpeedAtt(int mode, int speed);

int GetBonusSum();

int StartGameAtt(int mode, int game_start);

void* GetGameElement(int el);


void SetBonuses(Bonus* old_bonuses);

void SetRacket(Racket* old_racket);

void SetBall(Ball* old_ball);

int ScoreAtt(int mode, int sum);

int DstBricksAtt(int mode, int dst_bricks);

int LastMoveAtt(int mode, int move);