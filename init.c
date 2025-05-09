#include "2048.h"

void init_board(t_board *board)
{
	srand(time(NULL));
	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 5; b++)
		{
			board->tiles[a][b].number = 0;
			board->tiles[a][b].merged = false;
		}
	}
	if (board->size == 5)
		board->empty_tiles = 25;
	else
	{
		board->empty_tiles = 16;
		for (int a = 0; a < 5; a++)
			board->tiles[a][4].number = -1;
		for (int b = 0; b < 5; b++)
			board->tiles[4][b].number = -1;
	}
	board->game_over = false;
}
