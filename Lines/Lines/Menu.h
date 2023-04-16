#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define BTN_WIDTH 100
#define BTN_HEIGHT 50
#define BTN_INDENT 20 //расстояние между кнопками
#define START "Start"
#define QUIT "Quit"

typedef struct
{
	int x_centre_pos;
	int y_centre_pos;
	char name[20];
} Button;

void DrawMenu();

void SelectButton(int btn_num, int last_btn);