#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

/*

2021/03/04 - Palindrome Version 1.0.0

*/

#define MAX_N	11
#define MAX_STR 100001

using namespace std;

int n = 0;
char input_data[MAX_N][MAX_STR] = {};

int palindrome_sort(char* str, int lens)
{
	int i = 0;
	int half_lens = (int)ceil(double(lens / 2));
	int index1 = 0, index2 = (lens - 1);
	int err_cnt = 1, temp_result = 1;

	for (i = 0; i < half_lens; i++)
	{
		if (err_cnt >= 3)
			break;
		if (str[index1] == str[index2])
		{
			index1 += 1;
			index2 -= 1;
		}
		else
		{
			i--;
			index2 -= 1;
			err_cnt++;
		}
	}

	if (err_cnt != 1)
	{
		temp_result = err_cnt;
		index1 = 0;
		index2 = (lens - 1);
		err_cnt = 1;
		for (i = 0; i < half_lens; i++)
		{
			if (err_cnt >= 3)
				break;
			if (str[index1] == str[index2])
			{
				index1 += 1;
				index2 -= 1;
			}
			else
			{
				i--;
				index1 += 1;
				err_cnt++;
			}
		}
	}
	return min(temp_result, err_cnt);
}

int main() {
	int cnt = 0;
	int lens = 0;

	freopen("palin.inp", "r", stdin);
	freopen("palin.out", "w", stdout);
	setbuf(stdout, NULL);

	scanf("%d", &n);
	//printf("%d\n", n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", input_data[i]);
		//printf("input: %s\n", input_data[i]);
		lens = strlen(input_data[i]);
		printf("%d\n", palindrome_sort(input_data[i], lens));
	}

	return 0;
}