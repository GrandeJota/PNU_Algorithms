#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#include <ctime>
/*

2021/03/10 - Most Word Version 1.0.0 => ���⵵ O(n^2+n) ����
										case no.10 ���� 2�� �ʰ�
			 Most Word Version 2.0.0 => C++�� ���� ���⵵ O(3n) ����
										case no.8,9,10 ���� 2�� �ʰ�
			 Most Word Version 2.0.1 => C++�� ���� ���⵵ O(2.5n) ����
										insert�Լ��� �ð� ���⵵�� ��� ���߾���
			 Most Word Version 2.0.2 => C++�� ���� ���⵵ O(2n) ����
										������ ���ø�ŭ ���Եȵ� ���� ������ Ȯ���ϰ� ����
2021/03/11 - Most Word Version 3.0.0 => ���⵵ O(n) ����
										�ؽö� ���� ã�Ҵ�
2021/03/12 - Most Word Version 3.0.0
										Doxygen�� �ּ� �߰� �� �ڵ� refactoring
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
 * \brief  hash ���(string to key)
 * \detail MAX_BUCKET��ŭ ������ ������ ������ ��꿡 �߰���
 *		   Hach Collision�� 0% �� �ƴҵ� ������ �ִ��� ���ϰ� ���ġ�� ����
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
 * \brief   �ִ� �˻��� ã��
 * \detail  hash�� key������ Bucket �з��� ���� Bucket�� �ҷ��ö� Count ������ �ߺ� Ƚ���� �ѹ��� ���
 *          read�� ���ÿ� Bucket�з��� �ϹǷ� �Լ� �и� ����
 * \param   n : ���Ͽ� ����ִ� String��
 * \return  None
 * \warning Hash collision�� �Ͼ��� ��ó ����
 * \should  Hash collision ��� ó�� ��� �߰� �ʿ�
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
	//------�ð� ��� ����------//
	start = clock();

	//------�ý��� ����------//
	int n;

	freopen("words.inp", "r", stdin);
	freopen("words.out", "w", stdout); 

	scanf("%d", &n);

	find_peak(n);
	cout << output << "\n";

	//------�ð� ��� ��------//
	end = clock();
	//printf("%d msec\n", end-start);
	return 0;
}