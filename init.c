#include "2048.h"

void init_board(t_board *board)
{
	srand(time(NULL));
	for (int x = 0; x < board->size; x++)
	{
		for (int y = 0; y < board->size; y++)
		{
			board->tiles[y][x].number = 0;
			board->tiles[y][x].merged = false;
		}
	}
	board->empty_tiles = board->size * board->size;
	board->score = 0;
	board->game_over = false;
}
