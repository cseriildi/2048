#include "2048.h"

void	move_left(t_board *board, int x, int y)
{
	// printf("calling %s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
	for (int i = x; i < 5; i++)
	{
		if (board->tiles[y][i].number > 0)
		{
			printf("moving %i @ (%i,%i)\n", board->tiles[y][i].number, x, y);
			board->tiles[y][x].number = board->tiles[y][i].number;
			board->tiles[y][i].number = 0;
			break ;
		}
	}
}
