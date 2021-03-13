#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cmath>

#include <ctime>
/*

2021/03/12 - Card Deck Version 0.0.0 => 연립일차를 위한 데이터 처리과정까지 완료
										두가지 미지수를 구할수있는 코드를 구현하면 완성
2021/03/13 - Card Deck Version 0.0.1 => x+y=a, xy=b
										x=a/2+sqrt((a/2)^2-b)
										y=a/2-sqrt((a/2)^2-b)

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
	int missing_val[2] = { 0, 0 };
	double half_a = 0.0, sqmin_ab = 0.0, mk_minus = 1.0;

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
	missing_val[0] = total_n - sums;
	if (ab_cnt == 2)
	{
		half_a = (double)missing_val[0] / 2.0;
		sqmin_ab = ((half_a * half_a) - (double)facto_ori);
		if (sqmin_ab < 0.0)
		{
			mk_minus = -1.0;
		}
		sqmin_ab *= mk_minus;
		//printf("%f %f\n", half_a, sqmin_ab);
		missing_val[0] = (int)(half_a - mk_minus * sqrt(sqmin_ab)+0.5);
		missing_val[1] = (int)(half_a + mk_minus * sqrt(sqmin_ab)+0.5);

		printf("%d\n", min(missing_val[0], missing_val[1]));
	}
	printf("%d\n", max(missing_val[0], missing_val[1]));

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
	//printf("%d msec\n", end-start);
	return 0;
}  
