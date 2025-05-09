#include "2048.h"

void	debug_print(t_board *board)
{
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (board->tiles[x][y].number == -1)
				printf("X ");
			else
				printf("%d ", board->tiles[x][y].number);
		}
		printf("\n");
	}
}
