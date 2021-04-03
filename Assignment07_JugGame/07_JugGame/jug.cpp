#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define MAX_ITER 10
#define MAX_STONE 101
#define MASK_1BIT 0x01
#define ASCII_F 1 //first
#define ASCII_S 2 //second

int condition[3] = {};
int check_data[MAX_ITER] = {};
int winner_table[MAX_STONE] = {};

int find_winner(int n, int been_n)
{
	int result = 1;

	if (n < 0)
		return ASCII_F;

	if (winner_table[n] == ASCII_F || winner_table[n] == ASCII_S)
	{
		return winner_table[n];
	}

	if ((n - check_data[0]) == 0)
	{
		winner_table[n] = ASCII_F;
		return ASCII_F;
	}
	if ((n - check_data[1]) == 0)
	{
		winner_table[n] = ASCII_F;
		return ASCII_F;
	}
	if ((n - check_data[2]) == 0)
	{
		winner_table[n] = ASCII_F;
		return ASCII_F;
	}

	if (((find_winner((n - check_data[0]), check_data[0]) == ASCII_F)) &&
		(been_n != check_data[0]))
	{
		if (result == ASCII_F)
			result = ASCII_S;
		else
			result = ASCII_F;
	}
	if (((find_winner((n - check_data[1]), check_data[1]) == ASCII_F)) &&
		(been_n != check_data[1]))
	{
		if (result == ASCII_F)
			result = ASCII_S;
		else
			result = ASCII_F;
	}
	if (((find_winner((n - check_data[2]), check_data[2]) == ASCII_F)) &&
		(been_n != check_data[2]))
	{
		if (result == ASCII_F)
			result = ASCII_S;
		else
			result = ASCII_F;
	}
	winner_table[n] = result;
	return result;
}

int main()
{
	int result;

	freopen("jug.inp", "r", stdin);
	freopen("jug.out", "w", stdout);

	scanf("%d %d %d", &condition[0], &condition[1], &condition[2]);
	//printf("%d %d %d\n", condition[0], condition[1], condition[2]);

	for (int i = 0; i < MAX_ITER; i++)
	{
		scanf("%d", &check_data[i]);
		//printf("%d\n", check_data[i]);
		result = find_winner(check_data[i], 0);
		if(find_winner(check_data[i], 0) == ASCII_F)
			printf("F\n");
		else if(find_winner(check_data[i], 0) == ASCII_S)
			printf("S\n");
	}
	return 0;
}
