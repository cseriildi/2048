#include "2048.h"

void	merge_left(t_board *board, int x, int y)
{
	// printf("calling %s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
	int i = x + 1;
	if (i < 5)
	{
		if (board->tiles[y][i].number == board->tiles[y][x].number)
		{
			// printf("merging left %i @ (%i,%i)\n", board->tiles[y][i].number, x, y);
			board->tiles[y][x].number *= 2;
			board->tiles[y][i].number = 0;
			board->tiles[y][i].merged = true;
			board->empty_tiles++;
		}
	}
}

void	merge_right(t_board *board, int x, int y)
{
	// printf("calling %s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
	int i = x - 1;
	if (i >= 0)
	{
		if (board->tiles[y][i].number == board->tiles[y][x].number)
		{
			// printf("merging right %i @ (%i,%i)\n", board->tiles[y][i].number, x, y);
			board->tiles[y][x].number *= 2;
			board->tiles[y][i].number = 0;
			board->tiles[y][i].merged = true;
			board->empty_tiles++;
		}
	}
}

void	merge_up(t_board *board, int x, int y)
{
	// printf("calling %s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
	int i = y + 1;
	if (i < 5)
	{
		if (board->tiles[i][x].number == board->tiles[y][x].number)
		{
			// printf("merging up %i @ (%i,%i)\n", board->tiles[i][x].number, x, y);
			board->tiles[y][x].number *= 2;
			board->tiles[i][x].number = 0;
			board->tiles[i][x].merged = true;
			board->empty_tiles++;
		}
	}
}

void	merge_down(t_board *board, int x, int y)
{
	// printf("calling %s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
	int i = y - 1;
	if (i >= 0)
	{
		if (board->tiles[i][x].number == board->tiles[y][x].number)
		{
			// printf("merging down %i @ (%i,%i)\n", board->tiles[i][x].number, x, y);
			board->tiles[y][x].number *= 2;
			board->tiles[i][x].number = 0;
			board->tiles[i][x].merged = true;
			board->empty_tiles++;
		}
	}
}
