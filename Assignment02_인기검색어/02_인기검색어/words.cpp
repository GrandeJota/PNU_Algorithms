#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>

#include <time.h>
/*

2021/03/10 - Most Word Version 1.0.0 => ���⵵ O(n^2+n) ����
										case no.10 ���� 2�� �ʰ�
			 Most Word Version 2.0.0 => C++�� ���� ���⵵ O(3n) ����
										case no.8,9,10 ���� 2�� �ʰ�
			 Most Word Version 2.0.1 => C++�� ���� ���⵵ O(2.5n) ����
										insert�Լ��� �ð� ���⵵�� ��� ���߾���
			 Most Word Version 2.0.2 => C++�� ���� ���⵵ O(2n) ����
										������ ���ø�ŭ ���Եȵ� ���� ������ Ȯ���ϰ� ����

*/

using namespace std;

map<string, int> input_data;
string output = "NONE";

void word_peak(int n)
{
	int half_over = (int)((n / 2) + 1);
	string temp_str;
	map<string, int>::iterator iter;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < n; i++)
	{
		cin >> temp_str;
		if(input_data[temp_str] > 0)
		{
			input_data[temp_str]++;
		}
		else
			input_data.insert(pair<string, int>(temp_str, input_data[temp_str]++));
	}
	for (iter = input_data.begin(); iter != input_data.end(); ++iter)
	{
		if (iter->second >= half_over)
		{
			output = iter->first;
			return;
			//printf("test : %d\n", input_data[temp_str]);
		}
	}
}

int main()
{
	clock_t start, end;
	int n;
	start = clock();
	freopen("words.inp", "r", stdin);
	freopen("words.out", "w", stdout);

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	//cout << n;
	word_peak(n);
	cout << output << "\n";
	end = clock();
	printf("%d msec\n", end-start);
	return 0;
}