#include "2048.h"

static void	merge_helper(t_board *board, int x, int y)
{
	board->tiles[y][x].number *= 2;
	if (board->tiles[y][x].number == WIN_VALUE)
		board->win = true;
	board->empty_tiles++;
	board->spawn = true;
}

void	merge_left(t_board *board, int x, int y)
{
	int i = x + 1;
	if (i < board->size)
	{
		if (board->tiles[y][i].number == board->tiles[y][x].number)
		{
			merge_helper(board, x, y);
			board->tiles[y][i].number = 0;
			board->tiles[y][i].merged = true;
		}
	}
}

void	merge_right(t_board *board, int x, int y)
{
	int i = x - 1;
	if (i >= 0)
	{
		if (board->tiles[y][i].number == board->tiles[y][x].number)
		{
			merge_helper(board, x, y);
			board->tiles[y][i].number = 0;
			board->tiles[y][i].merged = true;
		}
	}
}

void	merge_up(t_board *board, int x, int y)
{
	int i = y + 1;
	if (i < board->size)
	{
		if (board->tiles[i][x].number == board->tiles[y][x].number)
		{
			merge_helper(board, x, y);
			board->tiles[i][x].number = 0;
			board->tiles[i][x].merged = true;
		}
	}
}

void	merge_down(t_board *board, int x, int y)
{
	int i = y - 1;
	if (i >= 0)
	{
		if (board->tiles[i][x].number == board->tiles[y][x].number)
		{
			merge_helper(board, x, y);
			board->tiles[i][x].number = 0;
			board->tiles[i][x].merged = true;
		}
	}
}
