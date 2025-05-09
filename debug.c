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
