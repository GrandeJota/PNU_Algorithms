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
char output[MAX_WORDLEN] = "NONE";

int compare(const void* a, const void* b)
{
	return strcmp((char*)a, (char*)b);
}

void word_sorting()
{
	int n;
	FILE* pFile = NULL;
	pFile = fopen("words.inp", "r");
	fgets(input_data[0], MAX_WORDLEN, pFile); // 첫줄 생략
	n = atoi(input_data[0]);
	int cnt = 1;
	int half_over_n = (int)((n / 2));
	for (int i = 0; i < n; i++)
	{
		fgets(input_data[i], MAX_WORDLEN, pFile);
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
			strcpy(output, strtok(input_data[i], "\n "));
			return;
		}
	}
	fclose(pFile);
}

int main()
{
	clock_t start, end;
	start = clock();
	freopen("words.out", "w", stdout);

	word_sorting();
	printf("%s\n", output);

	end = clock();
	//printf("%d msec\n", end-start);

	return 0;
}