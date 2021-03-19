#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

/*

2021/03/17 - Space Station Version 0.0.0 => 분할정복 오류 있음
											값이 정확하지 않음

*/

#define MOVE_MIN_WEI 0.00000001
#define MOVE_CEN_WEI 0.5

using namespace std;

int a[3], b[3], c[3], d[3];

typedef struct station
{
	double start[3];
	double center[3];
	double end[3];
	double c2s[3];
	double c2e[3];

	double s2s_r;
	double c2s_r;
	double e2s_r;
}station_t;

station_t AB, CD;
void find_centerP(double* a, double* b, double* center)
{
	center[0] = (a[0] + b[0]) / 2.0;
	center[1] = (a[1] + b[1]) / 2.0;
	center[2] = (a[2] + b[2]) / 2.0;
	/*printf("center %f %f %f\n", a[0], b[0], center[0]);
	printf("center %f %f %f\n", a[1], b[1], center[1]);
	printf("center %f %f %f\n", a[2], b[2], center[2]);*/
}
void find_moveC2SP(double* c, double* s, double* tmp_P)
{
	double t = MOVE_CEN_WEI - MOVE_MIN_WEI;
	tmp_P[0] = ((1 - t) * c[0]) + (t * s[0]);
	tmp_P[1] = ((1 - t) * c[1]) + (t * s[1]);
	tmp_P[2] = ((1 - t) * c[2]) + (t * s[2]);
}
void find_moveC2EP(double* c, double* e, double* tmp_P)
{
	double t = MOVE_CEN_WEI + MOVE_MIN_WEI;
	tmp_P[0] = ((1 - t) * c[0]) + (t * e[0]);
	tmp_P[1] = ((1 - t) * c[1]) + (t * e[1]);
	tmp_P[2] = ((1 - t) * c[2]) + (t * e[2]);
}

double get_range(double* a, double* c)
{
	double range;
	range = sqrt(pow(a[0] - c[0], 2) + pow(a[1] - c[1], 2) + pow(a[2] - c[2], 2));
	//printf("%f\n", range);
	return range;
}

void move_points(double* dst, double* src)
{
	memcpy(dst, src, sizeof(double)*3);
}
double get_range3times(station_t station1, station_t* station2)
{
	station2->s2s_r = get_range(station1.start, station2->start);
	station2->c2s_r = get_range(station1.start, station2->center);
	station2->e2s_r = get_range(station1.start, station2->end);

	return min(station2->s2s_r, min(station2->c2s_r, station2->e2s_r));
}
void get_shortestIn3(station_t station1, station_t* station2)
{
	double min_r, cmp_r1, cmp_r2;
	double tmp_P[3];
	min_r = min(station2->s2s_r, min(station2->c2s_r, station2->e2s_r));
	if (station2->s2s_r == min_r)
	{
		move_points(station2->end, station2->center);
	}
	else if (station2->c2s_r == min_r)
	{
		cmp_r1 = get_range(station2->c2s, station1.start);
		cmp_r2 = get_range(station2->c2e, station1.start);
		if (cmp_r1 >= cmp_r2)
		{
			move_points(station2->start, station2->center);
		}
		else
		{
			move_points(tmp_P, station2->start);
			move_points(station2->start, station2->center);
			move_points(station2->end, tmp_P);
		}
	}
	else if (station2->e2s_r == min_r)
	{
		move_points(tmp_P, station2->end);
		move_points(station2->end, station2->center);
		move_points(station2->start, tmp_P);
	}
}
void Pointinit(station_t* station)
{
	find_centerP(station->start, station->end, station->center);
	find_moveC2SP(station->center, station->start, station->c2s);
	find_moveC2EP(station->center, station->end, station->c2e);
}
double find_short()
{
	double result1, result2;
	int cnt = 0;
	while (1)
	{
		Pointinit(&AB);
		Pointinit(&CD);

		result1 = get_range3times(AB, &CD);
		get_shortestIn3(AB, &CD);
		Pointinit(&CD);

		result2 = get_range3times(CD, &AB);
		get_shortestIn3(CD, &AB);
		Pointinit(&AB);

		if (abs(result1 - result2) < MOVE_MIN_WEI)
		{
			cnt++;
			if (cnt > 1)
			{
				break;
			}
		}
		else
			cnt = 0;
	}
	return min(result1, result2);
}

int main()
{
	int result;
	freopen("station.inp", "r", stdin);
	freopen("station.out", "w", stdout);
	
	scanf("%d %d %d", &a[0], &a[1], &a[2]);
	scanf("%d %d %d", &b[0], &b[1], &b[2]);
	scanf("%d %d %d", &c[0], &c[1], &c[2]);
	scanf("%d %d %d", &d[0], &d[1], &d[2]);	
	AB.start[0] = (double)a[0]; AB.start[1] = (double)a[1]; AB.start[2] = (double)a[2];
	AB.end[0] = (double)b[0]; AB.end[1] = (double)b[1]; AB.end[2] = (double)b[2];
	CD.start[0] = (double)c[0]; CD.start[1] = (double)c[1]; CD.start[2] = (double)c[2];
	CD.end[0] = (double)d[0]; CD.end[1] = (double)d[1]; CD.end[2] = (double)d[2];

	//printf("%f %f %f %f %f\n", AB.start[0], AB.center[0], AB.end[0], AB.c2s[0], AB.c2e[0]);
	//printf("%f %f %f %f %f\n", CD.start[0], CD.center[0], CD.end[0], CD.c2s[0], CD.c2e[0]);

	result = (int)ceil(find_short());
	printf("%d\n", result);
	return 0;
}
