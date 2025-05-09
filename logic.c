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
					// printf("spawning @ (%i,%i):%i\n", x, y, number);
					board->empty_tiles--;
					return ;
				}
				tile--;
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

static void	traverse_board(t_board *board, t_direction dir,
			 void (*move)(t_board *, int, int),
			 void (*merge)(t_board *, int, int))
{
	// loop for moving left and up
	if (dir == LEFT || dir == UP)
	{
		for (int x = 0; x < 5; x++)
		{
			for (int y = 0; y < 5; y++)
			{
				move_and_merge(board, x, y, move, merge);
			}
		}
	}
	// loop for moving right and down
	else
	{
		for (int x = 4; x >= 0; x--)
		{
			for (int y = 4; y >= 0; y--)
			{
				move_and_merge(board, x, y, move, merge);
			}
		}
	}
}


static void	reset_merged(t_board *board)
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
		move = move_up;
		merge = merge_up;
	}
	else if (dir == DOWN)
	{
		move = move_down;
		merge = merge_down;
	}
	else if (dir == LEFT)
	{
		move = move_left;
		merge = merge_left;
	}
	else if (dir == RIGHT)
	{
		move = move_right;
		merge = merge_right;
	}
	else
	{
		printf("Invalid direction\n");
		return ;
	}
	traverse_board(board, dir, move, NULL);
	traverse_board(board, dir, NULL, merge);
	traverse_board(board, dir, move, NULL);
	reset_merged(board);
}

void game_loop(t_board *board)
{
	keypad(board->score_win.win, TRUE);
	int ch;
	while ((ch = wgetch(board->score_win.win)) != ESCAPE)
	{
		if (board->empty_tiles != 0)
			spawn_number(board);

		if (ch == KEY_UP)
			exec_move(board, UP);
		else if (ch == KEY_DOWN)
			exec_move(board, DOWN);
		else if (ch == KEY_LEFT)
			exec_move(board, LEFT);
		else if (ch == KEY_RIGHT)
			exec_move(board, RIGHT);
		update_board(board);
		//TODO: game over check
	}
}
