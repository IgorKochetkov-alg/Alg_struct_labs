#pragma once

#include "Resource.h"
#include <math.h>
#include <stdlib.h>

typedef struct {
	double x;
	double y;
} Point;

Point* Init();

void Geom(Point* points, int num, double* length, double* sin_a, double* cos_a);

void Centre(Point* points, int num, double* length, double* sin_a, double* cos_a);

Point* Step(Point* points, size_t n, size_t last_n, int* last_s, int* s, double* length,
	double* sin_a, double* cos_a);