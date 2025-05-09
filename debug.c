#include "2048.h"

void	debug_print(t_board *board)
{
	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 5; b++)
		{
			if (board->tiles[a][b].number == -1)
				printf("X ");
			else
				printf("%d ", board->tiles[a][b].number);
		}
		printf("\n");
	}
}
