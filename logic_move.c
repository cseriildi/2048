#include "2048.h"

void	move_left(t_board *board, int x, int y)
{
	// printf("calling %s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
	for (int i = x; i < board->size; i++)
	{
		if (board->tiles[y][i].number > 0)
		{
			// printf("moving left %i @ (%i,%i)\n", board->tiles[y][i].number, x, y);
			board->tiles[y][x].number = board->tiles[y][i].number;
			board->tiles[y][i].number = 0;
			break ;
		}
	}
}

void	move_right(t_board *board, int x, int y)
{
	// printf("calling %s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
	for (int i = x; i >= 0; i--)
	{
		if (board->tiles[y][i].number > 0)
		{
			// printf("moving right %i @ (%i,%i)\n", board->tiles[y][i].number, x, y);
			board->tiles[y][x].number = board->tiles[y][i].number;
			board->tiles[y][i].number = 0;
			break ;
		}
	}
}

void	move_down(t_board *board, int x, int y)
{
	// printf("calling %s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
	for (int i = y; i >= 0; i--)
	{
		if (board->tiles[i][x].number > 0)
		{
			// printf("moving down %i @ (%i,%i)\n", board->tiles[i][x].number, x, y);
			board->tiles[y][x].number = board->tiles[i][x].number;
			board->tiles[i][x].number = 0;
			break ;
		}
	}
}

void	move_up(t_board *board, int x, int y)
{
	// printf("calling %s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
	for (int i = y; i < board->size; i++)
	{
		if (board->tiles[i][x].number > 0)
		{
			// printf("moving up %i @ (%i,%i)\n", board->tiles[i][x].number, x, y);
			board->tiles[y][x].number = board->tiles[i][x].number;
			board->tiles[i][x].number = 0;
			break ;
		}
	}
}
