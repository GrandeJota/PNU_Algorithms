#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cmath>

#include <ctime>
/*

2021/03/12 - Card Deck Version 0.0.0 => 연립일차를 위한 데이터 처리과정까지 완료
										두가지 미지수를 구할수있는 코드를 구현하면 완성

*/

using namespace std;

#define OVERFLOW_BLOCK 10000000.0
#define OVERFLOW_DIV   10000.0

long double factos = 1.0;
long double facto_ori = 1.0;
int sums = 0;
int overs_cnt = 0;
int overs_ori = 0;

void overflow_prevent(int *overs)
{
	(*overs)++;
}
void rewind_overflow(int* overs)
{
	(*overs)--;
}

void facto_origin(int n)
{
	for (int i = 1; i <= n; i++)
	{
		facto_ori *= (long double)i;
		if (facto_ori > OVERFLOW_BLOCK)
		{
			facto_ori /= OVERFLOW_DIV;
			overflow_prevent(&overs_ori);
		}
	}
}

void find_missing(int n)
{
	int total_n = n * (n + 1) / 2;
	int temp;
	int input_cnt = 0, ab_cnt = 0;
	int first_miss = 0, second_miss = 0;

	for (int i = 0; i < n; i++)
	{
		if (scanf("%d", &temp) == -1)
		{
			input_cnt = i;
			break;
		}
		sums += temp;
		/*factos *= (long double)temp;
		if (factos > OVERFLOW_BLOCK)
		{
			factos /= OVERFLOW_DIV;
			overflow_prevent(&overs_cnt);
		}
		printf("%lf * 10^%d\n", factos, overs_cnt);*/
		facto_ori /= (long double)temp;
		if (facto_ori < OVERFLOW_DIV && overs_ori > 0)
		{
			facto_ori *= OVERFLOW_DIV;
			rewind_overflow(&overs_ori);
		}
	}
	ab_cnt = (n - input_cnt);
	first_miss = total_n - sums;
	printf("%d\n", first_miss);
	printf("%lf * 10^%d\n", facto_ori, overs_ori);

	return;
}

int main()
{
	clock_t start, end;
	start = clock();

	int n;

	freopen("deck.inp", "r", stdin);
	freopen("deck.out", "w", stdout);

	scanf("%d", &n);
	facto_origin(n);
	find_missing(n);

	end = clock();
	printf("%d msec\n", end-start);
	return 0;
}  
