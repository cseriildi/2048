#include "2048.h"

void	spawn_number(t_board *board)
{
	short tile;
	short number;
	
	tile =  rand() % (board->empty_tiles);
	number = rand() % 10;
	if (number < 9)
		number = 2;
	else
		number = 4;
	printf("tile: %d || number: %d\n", tile, number);
	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 5; b++)
		{
			if (board->tiles[a][b].number == 0)
			{
				if (tile == 0)
				{
					board->tiles[a][b].number = number;
					board->empty_tiles--;
					return ;
				}
				tile--;
			}
		}
	}
}
