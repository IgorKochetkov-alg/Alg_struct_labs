#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "Arcanoid.h"

#define BTN_NUM 6
#define START "Start"
#define OPTIONS "Options"
#define END "Exit"
#define BTN_WIDTH 100
#define BTN_HEIGHT 50
#define BTN_INDENT 20
#define NAME_SIZE 20
#define EASY "Easy"
#define MEDIUM "Medium"
#define HARD "Hard"

typedef struct
{
	point centre_pos;
	char name[NAME_SIZE];
} Button;


Button* SystemInit(Button* buttons);
void DrawMenu(Button* buttons, int btn_num);
void DrawBtn(HWND hWnd, Button* buttons, int btn_num, int last_btn);