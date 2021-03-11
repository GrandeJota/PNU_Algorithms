#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <time.h>
/*

2021/03/10 - Most Word Version 1.0.0 => 복잡도 O(n^2+n) 예상
										case no.10 실패 2초 초과
2021/03/11 - Most Word Version 1.1.0 => 복잡도 O(2*n+nlog n) 예상
										qsort를 이용해서 검증

*/

using namespace std;

#define MAX_N 1000001
#define MAX_WORDLEN 256 // 기네스 등재 제일 긴 단어 45자(비공식 189819자)

char input_data[MAX_N][MAX_WORDLEN] = {};
int  record_cnt[MAX_N] = { 1 };
bool checked_index[MAX_N] = { false };
char output[MAX_WORDLEN] = "NONE";

int compare(const void* a, const void* b)
{
	return strcmp((char*)a, (char*)b);
}

void word_sorting(int n)
{
	int cnt = 1;
	int half_over_n = (int)((n / 2));
	for (int i = 0; i < n; i++)
	{
		scanf("%s", input_data[i]);
		//printf("%s\n", input_data[i]);
	}
	qsort(input_data, n, sizeof(input_data[0]), compare);
	for (int i = 1; i < n; i++)
	{
		if (!compare(input_data[i], input_data[i - 1]))
		{
			cnt++;
		}
		else
		{
			cnt = 1;
		}

		if (cnt >= half_over_n)
		{
			strcpy(output, input_data[i]);
			return;
		}
	}
}

int main()
{
	clock_t start, end;
	int n;
	char word_n1[MAX_WORDLEN] = {};

	start = clock();
	freopen("words.inp", "r", stdin);
	freopen("words.out", "w", stdout);

	scanf("%d", &n);
	word_sorting(n);
	printf("%s\n", output);

	end = clock();
	printf("%d msec\n", end-start);

	return 0;
}