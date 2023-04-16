#include "fractal.h"
#include <math.h>


Point* Init()
{
	Point* points = (Point*)calloc(2, sizeof(Point));
	return points;
}

void Geom(Point* points, int num, double* length, double* sin_a, double* cos_a)
{
	*length = sqrt(pow((points[num + 4].x - points[num].x), 2) + pow((points[num + 4].y - points[num].y), 2));
	*sin_a = (points[num + 4].y - points[num].y) / (*length);
	*cos_a = (points[num + 4].x - points[num].x) / (*length);
}

void Centre(Point* points, int num, double* length, double* sin_a, double* cos_a)
{
    double ax1, ay1, bx1, by1, cx1, cy1;
    ax1 = (points[num - 2].y * (*sin_a) + points[num - 2].x * (*cos_a));
    bx1 = (points[num + 2].y * (*sin_a) + points[num + 2].x * (*cos_a));
    ay1 = (ax1 * (*cos_a) - points[num - 2].x) / (*sin_a);
    by1 = (bx1 * (*cos_a) - points[num + 2].x) / (*sin_a);
    cx1 = (ax1 + bx1) / 2;
    if (ax1 < bx1)
    {
        cy1 = ay1 - *length / (2 * sqrt(3.0));
    }
    if (ax1 > bx1)
    {
        cy1 = ay1 + *length / (2 * sqrt(3.0));
    }
    points[num].x = cx1 * (*cos_a) - cy1 * (*sin_a);
    points[num].y = cx1 * (*sin_a) + cy1 * (*cos_a);
    return;
}


Point* Step(Point* points, size_t n, size_t last_n, int* last_s, int* s, double* length,
    double* sin_a, double* cos_a)
{
    if (n > last_n)
    {
        *last_s = *s;

        *s = *s + (int)pow(4.0, n - 1) * 3;
        points = (Point*)realloc(points, *s * sizeof(Point));
        for (int i = *last_s - 1; i >= 0; i--)
        {
            points[i * 4].x = points[i].x;
            points[i * 4].y = points[i].y;
        }


        for (int i = 0; i < *s; i++)
        {
            if ((i % 4) == 0)
            {
                Geom(points, i, length, sin_a, cos_a);
            }
            if ((i % 4) == 1)
            {
                points[i].x = points[i - 1].x + *length * *cos_a / 3;
                points[i].y = points[i - 1].y + *length * *sin_a / 3;
            }
            if ((i % 4) == 2)
            {
                Centre(points, i, length, sin_a, cos_a);
            }
            if ((i % 4) == 3)
            {
                points[i].x = points[i - 3].x + 2 * *length * *cos_a / 3;
                points[i].y = points[i - 3].y + 2 * *length * *sin_a / 3;
            }
        }
    }
    return points;
}