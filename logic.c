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
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (board->tiles[y][x].number == 0)
			{
				if (tile == 0)
				{
					board->tiles[y][x].number = number;
					printf("spawning @ (%i,%i):%i\n", x, y, number);
					board->empty_tiles--;
					return ;
				}
				tile--;
			}
		}
	}
}

// move process
// move first, then merge, then move again to fill gaps

void	traverse_board(t_board *board,
			 void (*move)(t_board *, int, int),
			 void (*merge)(t_board *, int, int))
{
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (board->tiles[y][x].number == 0)
			{
				// printf("%s @ (%i,%i):%i\n", __func__, x, y, board->tiles[y][x].number);
				if (move) move(board, x, y);
				// if (move) printf("move function pointer okay\n");
			}
			else if (board->tiles[y][x].number > 0 && board->tiles[y][x].merged == false)
			{
				if (merge) merge(board, x, y);
				// if (merge) printf("merge function pointer okay\n");
			}
		}
	}
	(void)move;
	(void)merge;
}


void	reset_merged(t_board *board)
{
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			board->tiles[y][x].merged = false;
		}
	}
}

void	exec_move(t_board *board, t_direction dir)
{
	void	(*move)(t_board *, int, int);
	void	(*merge)(t_board *, int, int);

	if (dir == UP)
	{
		move = NULL; // TODO: implement
		merge = NULL; // TODO: implement
	}
	else if (dir == DOWN)
	{
		move = NULL; // TODO: implement
		merge = NULL; // TODO: implement
	}
	else if (dir == LEFT)
	{
		move = move_left;
		merge = merge_left;
	}
	else if (dir == RIGHT)
	{
		move = NULL; // TODO: implement
		merge = NULL; // TODO: implement
	}
	else
	{
		printf("Invalid direction\n");
		return ;
	}
	traverse_board(board, move, NULL);
	traverse_board(board, NULL, merge);
	traverse_board(board, move, NULL);
	reset_merged(board);
}


/*
// merge if right is the same number
				for (int i = x + 1; i < 5; i++)
				{
					if (board->tiles[i][y].number == board->tiles[y][x].number)
					{
						board->tiles[i][ynumber].number *= 2;
						board->tiles[i][y].number = 0;
						board->empty_tiles++;
						break ;
						}
						// just move
						else if (board->tiles[i][y].number == 0)
						{
							board->tiles[x][i].number = board->tiles[y][x].number;
							board->tiles[y][x].number = 0;
							board->empty_tiles--;
							y--;
							break ;
							}
							else if (board->tiles[x][i].number != 0)
							break ;
				}
*/