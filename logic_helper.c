#include "2048.h"

static void	move_and_merge(
				t_board *board,
				int x,
				int y,
				void (*tile_move)(t_board *, int, int),
				void (*merge)(t_board *, int, int));

void	reset_merged(t_board *board)
{
	for (int x = 0; x < board->size; x++)
	{
		for (int y = 0; y < board->size; y++)
		{
			board->tiles[y][x].merged = false;
		}
	}
}

void	traverse_board(t_board *board, t_direction dir,
						void (*move)(t_board *, int, int),
						void (*merge)(t_board *, int, int))
{
	// loop for moving left and up
	if (dir == LEFT || dir == UP)
	{
		for (int x = 0; x < board->size; x++)
		{
			for (int y = 0; y < board->size; y++)
			{
				move_and_merge(board, x, y, move, merge);
			}
		}
	}
	// loop for moving right and down
	else
	{
		for (int x = board->size - 1; x >= 0; x--)
		{
			for (int y = board->size - 1; y >= 0; y--)
			{
				move_and_merge(board, x, y, move, merge);
			}
		}
	}
}

static void	move_and_merge(t_board *board, int x, int y,
	void (*tile_move)(t_board *, int, int),
	void (*merge)(t_board *, int, int))
{
	if (board->tiles[y][x].number == 0)
	{
		if (tile_move) tile_move(board, x, y);
	}
	else if (board->tiles[y][x].number > 0 && board->tiles[y][x].merged == false)
	{
		if (merge) merge(board, x, y);
	}
}
