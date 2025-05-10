#include "2048.h"

void	move_left(t_board *board, int x, int y)
{
	for (int i = x; i < board->size; i++)
	{
		if (board->tiles[y][i].number > 0)
		{
			board->tiles[y][x].number = board->tiles[y][i].number;
			board->tiles[y][i].number = 0;
			board->spawn = true;
			break ;
		}
	}
}

void	move_right(t_board *board, int x, int y)
{
	for (int i = x; i >= 0; i--)
	{
		if (board->tiles[y][i].number > 0)
		{
			board->tiles[y][x].number = board->tiles[y][i].number;
			board->tiles[y][i].number = 0;
			board->spawn = true;
			break ;
		}
	}
}

void	move_down(t_board *board, int x, int y)
{
	for (int i = y; i >= 0; i--)
	{
		if (board->tiles[i][x].number > 0)
		{
			board->tiles[y][x].number = board->tiles[i][x].number;
			board->tiles[i][x].number = 0;
			board->spawn = true;
			break ;
		}
	}
}

void	move_up(t_board *board, int x, int y)
{
	for (int i = y; i < board->size; i++)
	{
		if (board->tiles[i][x].number > 0)
		{
			board->tiles[y][x].number = board->tiles[i][x].number;
			board->tiles[i][x].number = 0;
			board->spawn = true;
			break ;
		}
	}
}
