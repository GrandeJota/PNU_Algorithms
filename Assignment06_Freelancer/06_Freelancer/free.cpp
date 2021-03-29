#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define MAX_N 101

struct compare {
	bool operator()(pair<int, int>a, pair<int, int>b)
	{
		if (a.first != b.first)
			return a.first > b.first;
		else if (a.first == b.first)
			return a.second < b.second;
	}
};

typedef struct HCC {
	int start;
	int end;
	int cash;
}HCC_t;

typedef struct Result {
	int cash;
	int days;
}Result_t;
HCC_t input_data[MAX_N];
Result_t result;

int cal_days(int start, int end)
{
	return end - start + 1;
}

Result_t find_optimal(int n)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, compare> Temp;
	Result_t ret_value;
	Result_t W_include, W_exclude;

	if (n == 1)
	{
		ret_value.cash = input_data[0].cash;
		ret_value.days = cal_days(input_data[0].start, input_data[0].end);
		return ret_value;
	}
	else
	{
	}
}

int main()
{
	int n;

	freopen("free.inp", "r", stdin);
	freopen("free.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d", &input_data[i].start, &input_data[i].end, &input_data[i].cash);
		//printf("%d, %d, %d\n", input_data[i].start, input_data[i].end, input_data[i].cash);
	}
	result = find_optimal(n);
	printf("%d %d\n", result.cash, result.days);
	return 0;
}
