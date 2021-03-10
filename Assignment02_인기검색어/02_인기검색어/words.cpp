#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

/*

2021/03/10 - Most Word Version 1.0.0 => 복잡도 O(n^2+n) 예상
										case no.10 실패 2초 초과

*/

using namespace std;

#define MAX_N 1000001
#define MAX_WORDLEN 50 // 기네스 등재 제일 긴 단어 45자(비공식 189819자)

char input_data[MAX_N][MAX_WORDLEN] = {};
int  record_cnt[MAX_N] = { 1 };
bool checked_index[MAX_N] = { false };
char output[MAX_WORDLEN] = "NONE";

void word_sorting(int n)
{
	int j = 0;
	int half_over_n = (int)((n / 2) + 1);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", input_data[i]);
		//printf("%s\n", input_data[i]);
	}
	for (int j = 0; j < n; j++)
	{
		if (checked_index[j] == true)
			continue;

		for (int i = 1; i < n; i++)
		{
			if (!strcmp(input_data[j], input_data[i]))
			{
				//printf("index: %d[%s] record: %d\n", i, input_data[j], record_cnt[j]+1);
				checked_index[i] = true;
				record_cnt[j]++;
				if (record_cnt[j]+1 > half_over_n)
				{
					strcpy(output, input_data[j]);
					return;
				}
			}
		}
	}
}

int main()
{
	int n;
	char word_n1[MAX_WORDLEN] = {};

	freopen("words.inp", "r", stdin);
	freopen("words.out", "w", stdout);

	scanf("%d", &n);
	word_sorting(n);
	printf("%s\n", output);

	return 0;
}