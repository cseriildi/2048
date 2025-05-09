#include "2048.h"

void init_board(t_board *board)
{
	srand(time(NULL));
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			board->tiles[y][x].number = 0;
			board->tiles[y][x].merged = false;
		}
	}
	if (board->size == 5)
		board->empty_tiles = 25;
	else
	{
		board->empty_tiles = 16;
		for (int x = 0; x < 5; x++)
			board->tiles[4][x].number = -1;
		for (int y = 0; y < 5; y++)
			board->tiles[y][4].number = -1;
	}
	board->game_over = false;
}
