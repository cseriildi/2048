#include "2048.h"

void	debug_print(t_board *board)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			if (board->tiles[y][x].number == -1)
				printf("X ");
			else
				printf("%d ", board->tiles[y][x].number);
		}
		printf("\n");
	}
}

void	debug_move(t_board *board)
{
	debug_print(board);
	sleep(1);
	int rand_num = rand();
	if (rand_num % 4 == 0)
		exec_move(board, UP);
	else if (rand_num % 3 == 0)
		exec_move(board, LEFT);
	else if (rand_num % 5 == 0)
		exec_move(board, RIGHT);
	else
		exec_move(board, DOWN);
	debug_print(board);
	sleep(2);
	printf("\n");
}

void	debug_numbers(t_board *board)
{
	board->tiles[0][0].number = 2;
	board->tiles[0][1].number = 4;
	board->tiles[0][2].number = 8;
	board->tiles[0][3].number = 16;
	board->tiles[0][4].number = 32;
	board->tiles[1][0].number = 64;
	board->tiles[1][1].number = 128;
	board->tiles[1][2].number = 256;
	board->tiles[1][3].number = 512;
	board->tiles[1][4].number = 1024;
	board->tiles[2][0].number = 2048;
	board->tiles[2][1].number = 4096;
	board->tiles[2][2].number = 8192;
	board->tiles[2][3].number = 16384;
	board->tiles[2][4].number = 32768;
	board->tiles[3][0].number = 65536;
	board->tiles[3][1].number = 131072;
}
