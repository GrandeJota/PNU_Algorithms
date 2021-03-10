#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>

#include <time.h>
/*

2021/03/10 - Most Word Version 1.0.0 => 복잡도 O(n^2+n) 예상
										case no.10 실패 2초 초과
			 Most Word Version 2.0.0 => C++로 변경 복잡도 O(3n) 예상
										case no.8,9,10 실패 2초 초과
			 Most Word Version 2.0.1 => C++로 변경 복잡도 O(2.5n) 예상
										insert함수의 시간 복잡도를 고려 못했었음
			 Most Word Version 2.0.2 => C++로 변경 복잡도 O(2n) 예상
										과반이 나올만큼 집게된뒤 부터 과반을 확인하게 변경

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