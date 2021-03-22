#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

#define MAX_SIZE	1002
using namespace std;

struct compare {
	bool operator()(pair<int, int>a, pair<int, int>b)
	{
		if(a.first != b.first)
			return a.first > b.first;
		else if (a.first == b.first)
			return a.second > b.second;
	}
};

// 좌측 하단 (x,y) = (1,1) 부터 시작
int input_data[MAX_SIZE][MAX_SIZE];
int checked_data[MAX_SIZE][MAX_SIZE];
priority_queue<pair<int, int>, vector<pair<int, int>>, compare> xy_point;

int find_MaxPoint(int n, int m, int maxed)
{
	int cnt = 0;
	for (int i = n - (maxed - 1); i > 0; i--)
	{
		for (int j = maxed; j <= m; j++)
		{
			if (maxed == checked_data[i][j])
			{
				xy_point.push({ j - (maxed - 1), n - (i - 1) - (maxed - 1) });
				cnt++;
			}
		}
	}
	return cnt;
}

int find_square(int n, int m)
{
	int keep_max = 0, cnt;

	for (int i = n - 1; i > 0; i--)
	{
		for (int j = 2; j <= m; j++)
		{
			if (input_data[i][j] == 0)
			{
				checked_data[i][j] += (min(checked_data[i + 1][j - 1], min(checked_data[i + 1][j], checked_data[i][j - 1])) + 1);
				keep_max = max(keep_max, checked_data[i][j]);
			}
		}
	}
	return keep_max;
}

void find_BallParkArea(int n, int m)
{
	int keep_max = 0, cnt;

	keep_max = find_square(n, m);
	cnt = find_MaxPoint(n, m, keep_max);

	printf("%d %d\n", keep_max, cnt);
	for (int i = 0; i < cnt; i++)
	{
		printf("%d %d\n", xy_point.top().first, xy_point.top().second);
		xy_point.pop();
	}
}

int main()
{
	int N, M;

	freopen("ballpark.inp", "r", stdin);
	freopen("ballpark.out", "w", stdout);

	scanf("%d %d", &N, &M);
	//printf("%d %d\n", N, M);

	for (int x = 1; x <= N; x++)
	{
		for (int y = 1; y <= M; y++)
		{
			scanf("%1d", &input_data[x][y]);
			//printf("%d", input_data[x][y]);
		}
	}

	find_BallParkArea(N, M);

	return 0;
}
