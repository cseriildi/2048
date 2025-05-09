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
