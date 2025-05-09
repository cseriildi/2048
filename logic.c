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
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (board->tiles[x][y].number == 0)
			{
				if (tile == 0)
				{
					board->tiles[x][y].number = number;
					board->empty_tiles--;
					return ;
				}
				tile--;
			}
		}
	}
}
