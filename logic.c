#include "2048.h"

void	spawn_number(t_board *board)
{
	short tile;
	short number;
	
	if (!board->spawn)
		return ;
	tile =  rand() % (board->empty_tiles);
	number = rand() % 10;
	if (number < 9)
		number = 2;
	else
		number = 4;
	for (int x = 0; x < board->size; x++)
	{
		for (int y = 0; y < board->size; y++)
		{
			if (board->tiles[y][x].number == 0)
			{
				if (tile == 0)
				{
					board->tiles[y][x].number = number;
					board->empty_tiles--;
					board->spawn = false;
					return ;
				}
				tile--;
			}
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
		check_game_over(board);
		if (!board->game_over)
		{
			if (ch == KEY_UP)
				exec_move(board, UP);
			else if (ch == KEY_DOWN)
				exec_move(board, DOWN);
			else if (ch == KEY_LEFT)
				exec_move(board, LEFT);
			else if (ch == KEY_RIGHT)
				exec_move(board, RIGHT);
			if (board->empty_tiles != 0)
				spawn_number(board);
			update_board(board);
		}
	}
}
