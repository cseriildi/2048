#include "2048.h"

static void	merge_helper(t_board *board, int x, int y)
{
	board->tiles[y][x].number *= 2;
	board->score += board->tiles[y][x].number;
	if (board->tiles[y][x].number == WIN_VALUE)
		board->win = true; //TODO: write something if the player wins
	board->empty_tiles++;
	board->spawn = true;
}

void	merge_left(t_board *board, int x, int y)
{
	if (x + 1 < board->size && board->tiles[y][x + 1].number == board->tiles[y][x].number)
	{
		merge_helper(board, x, y);
		board->tiles[y][x + 1].number = 0;
		board->tiles[y][x + 1].merged = true;
	}
}

void	merge_right(t_board *board, int x, int y)
{
	if (x - 1 >= 0 && board->tiles[y][x - 1].number == board->tiles[y][x].number)
	{
		merge_helper(board, x, y);
		board->tiles[y][x - 1].number = 0;
		board->tiles[y][x - 1].merged = true;
	}
}

void	merge_up(t_board *board, int x, int y)
{
	if (y + 1 < board->size && board->tiles[y + 1][x].number == board->tiles[y][x].number)
	{
		merge_helper(board, x, y);
		board->tiles[y + 1][x].number = 0;
		board->tiles[y + 1][x].merged = true;
	}
}

void	merge_down(t_board *board, int x, int y)
{
	if (y - 1 >= 0 && board->tiles[y - 1][x].number == board->tiles[y][x].number)
	{
		merge_helper(board, x, y);
		board->tiles[y - 1][x].number = 0;
		board->tiles[y - 1][x].merged = true;
	}
}
