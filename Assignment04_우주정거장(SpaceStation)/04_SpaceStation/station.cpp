#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

/*

2021/03/17 - Space Station Version 0.0.0 => 분할정복 오류 있음
											값이 정확하지 않음

*/

using namespace std;

int a[3], b[3], c[3], d[3];
double p[3][3], q[3][3];
double center_p[3], center_q[3];
double range_p = 0.0, range_q = 0.0 ;

void find_centerP(double* a, double* b, double* center)
{
	center[0] = (a[0] + b[0]) / 2.0;
	center[1] = (a[1] + b[1]) / 2.0;
	center[2] = (a[2] + b[2]) / 2.0;
	/*printf("center %f %f %f\n", a[0], b[0], center[0]);
	printf("center %f %f %f\n", a[1], b[1], center[1]);
	printf("center %f %f %f\n", a[2], b[2], center[2]);*/
}

double get_range(double* a, double* c)
{
	double range;
	range = sqrt(pow(a[0] - c[0], 2) + pow(a[1] - c[1], 2) + pow(a[2] - c[2], 2));
	//printf("%f\n", range);
	return range;
}

double cmp_trirange(double* ranges, int* index)
{
	double min_range;
	min_range = min(ranges[0], min(ranges[1], ranges[2]));
	//printf("%f\n", min_range);
	if (ranges[0] == min_range)
	{
		index[0] = 0;
		index[1] = 1;
	}
	else if (ranges[1] == min_range)
	{
		if ((ranges[0] - ranges[2]) <= 0)
		{
			index[0] = 1;
			index[1] = 0;
		}
		else
		{
			index[0] = 1;
			index[1] = 2;
		}
	}
	else if (ranges[2] == min_range)
	{
		index[0] = 2;
		index[1] = 1;
	}
	return min_range;
}

double find_short()
{
	double result = 0.0, temp_result[3];
	double temp_rp[3], temp_rq[3];
	int keep_index[2] = {0};
	double tmp_p[3], tmp_q[3];

	while (1)
	{
		temp_rp[0] = get_range(p[0], q[0]);
		temp_rp[1] = get_range(p[0], q[1]);
		temp_rp[2] = get_range(p[0], q[2]);
		range_p = cmp_trirange(temp_rp, keep_index);
		/*printf("%d %d\n", keep_index[0], keep_index[1]);
		printf("%f %f %f\n", q[0][0], q[0][1], q[0][2]);
		printf("%f %f %f\n", q[1][0], q[1][1], q[1][2]);
		printf("%f %f %f\n", q[2][0], q[2][1], q[2][2]);*/

		memcpy(tmp_q, q[keep_index[0]], sizeof(q[0]));
		memcpy(q[2], q[keep_index[1]], sizeof(q[2]));
		memcpy(q[0], tmp_q, sizeof(q[0]));
		find_centerP(q[0], q[2], q[1]);

		temp_rp[0] = get_range(q[0], p[0]);
		temp_rp[1] = get_range(q[0], p[1]);
		temp_rp[2] = get_range(q[0], p[2]);
		range_q = cmp_trirange(temp_rp, keep_index);
		/*printf("%d %d\n", keep_index[0], keep_index[1]);
		printf("%f %f %f\n", p[0][0], p[0][1], p[0][2]);
		printf("%f %f %f\n", p[1][0], p[1][1], p[1][2]);
		printf("%f %f %f\n\n", p[2][0], p[2][1], p[2][2]);*/

		memcpy(tmp_p, p[keep_index[0]], sizeof(p[0]));
		memcpy(p[2], p[keep_index[1]], sizeof(p[2]));
		memcpy(p[0], tmp_p, sizeof(p[0]));
		find_centerP(p[0], p[2], p[1]);
		//printf("%f %f\n\n", range_p, range_q);
		if (abs(range_p - range_q) <= 0.00000001)
			break;
	}
	result = range_p;
	return result;
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

	p[0][0] = (double)a[0]; p[0][1] = (double)a[1]; p[0][2] = (double)a[2];
	p[2][0] = (double)b[0]; p[2][1] = (double)b[1]; p[2][2] = (double)b[2];
	q[0][0] = (double)c[0]; q[0][1] = (double)c[1]; q[0][2] = (double)c[2];
	q[2][0] = (double)d[0]; q[2][1] = (double)d[1]; q[2][2] = (double)d[2];
	find_centerP(p[0], p[2], p[1]);
	find_centerP(q[0], q[2], q[1]);

	result = ceil(find_short());
	printf("%d\n", result);
	return 0;
}
