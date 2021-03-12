#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#include <ctime>
/*

2021/03/10 - Most Word Version 1.0.0 => ���⵵ O(n^2+n) ����
										case no.10 ���� 2�� �ʰ�
			 Most Word Version 2.0.0 => C++로 변경 복잡도 O(3n) 예상
										case no.8,9,10 실패 2초 초과
			 Most Word Version 2.0.1 => C++로 변경 복잡도 O(2.5n) 예상
										insert함수의 시간 복잡도를 고려 못했었음
			 Most Word Version 2.0.2 => C++로 변경 복잡도 O(2n) 예상
										과반이 나올만큼 집게된뒤 부터 과반을 확인하게 변경
2021/03/11 - Most Word Version 3.0.0 => 복잡도 O(n) 예상
										해시란 것을 찾았다
2021/03/12 - Most Word Version 3.0.0
										Doxygen용 주석 추가 및 코드 refactoring
										Git update
*/

using namespace std;

#define MAX_N		1000001
#define MAX_WLEN	256
#define MAX_BUCKET MAX_N

string output = "NONE";
int    hash_table[MAX_BUCKET] = {};
string hash_value[MAX_BUCKET] = {};
char   input_data[MAX_N][MAX_WLEN] = {};

/**
 * \brief  hash 계산(string to key)
 * \detail MAX_BUCKET만큼 구분이 가도록 나머지 계산에 추가함
 *		   Hach Collision이 0% 는 아닐듯 하지만 최대한 피하게 계산치를 넣음
 * \param  str : string
 * \param  len : string length
 * \return hashed key value
 * \date   2021-03-12
 * \author Grandech
 */
int cal_hash(char* str, int len)
{
	int hashed = 401;
	for (int i = 0; i < len; i++)
	{
		hashed = ((hashed<<4) + str[i]) % MAX_BUCKET;
	}
	return hashed % MAX_BUCKET;
}

/**
 * \brief   최대 검색어 찾기
 * \detail  hash된 key값으로 Bucket 분류후 같은 Bucket이 불러올때 Count 증가로 중복 횟수도 한번에 계산
 *          read와 동시에 Bucket분류를 하므로 함수 분리 안함
 * \param   n : 파일에 들어있는 String수
 * \return  None
 * \warning Hash collision이 일어날경우 대처 없음
 * \should  Hash collision 대비 처리 방식 추가 필요
 * \date    2021-03-12
 * \author  Grandech
 */
void find_peak(int n)
{
	int half_over = (int)((n / 2));
	int hashed_key;

	for (int i = 0; i < n; i++)
	{
		scanf("%s", input_data[i]);
		hashed_key = cal_hash(input_data[i], strlen(input_data[i]));
		hash_table[hashed_key]++;
		if (hash_value[hashed_key].empty())
			hash_value[hashed_key] = input_data[i];
	}
	for (int i = 0; i < n; i++)
	{
		hashed_key = cal_hash(input_data[i], strlen(input_data[i]));

		if (hash_table[hashed_key] > half_over)
		{
			output = hash_value[hashed_key];
			return;
		}
	}

	return;
}

int main()
{
	clock_t start, end;
	//------시간 기록 시작------//
	start = clock();

	//------시스템 시작------//
	int n;

	freopen("words.inp", "r", stdin);
	freopen("words.out", "w", stdout);

	scanf("%d", &n);

	find_peak(n);
	cout << output << "\n";

	//------시간 기록 끝------//
	end = clock();
	//printf("%d msec\n", end-start);
	return 0;
}