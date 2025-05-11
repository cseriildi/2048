#include "2048.h"

void	spawn_number(t_board *board)
{
	short tile = rand() % board->empty_tiles;
	short number = (rand() % 10 == 0) ? 4 : 2;
	
	for (int x = 0; x < board->size; x++)
	{
		for (int y = 0; y < board->size; y++)
		{
			if (board->tiles[y][x].number == 0)
			{
				if (tile-- == 0)
				{
					board->tiles[y][x].number = number;
					if (board->tiles[y][x].number > board->max_tile_value)
						board->max_tile_value = board->tiles[y][x].number;
					board->empty_tiles--;
					board->spawn = false;
					return ;
				}
			}
		}
	}
}

void	exec_move(t_board *board, t_direction dir)
{
	void	(*move)(t_board *, int, int);
	void	(*merge)(t_board *, int, int);

	switch (dir)
	{
	case UP:
		move = move_up;
		merge = merge_up;
		break;
	case DOWN:
		move = move_down;
		merge = merge_down;
		break;
	case LEFT:
		move = move_left;
		merge = merge_left;
		break;
	case RIGHT:
		move = move_right;
		merge = merge_right;
		break;
	default:
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
	while ((ch = wgetch(board->score_win.win)) != ESCAPE
		&& resize_gameloop(board, ch) == SUCCESS)
	{
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
			else
				continue;

			if (board->spawn)
			{	
				spawn_number(board);
				update_board(board);
				update_score(board);
			}
		}
		check_game_over(board);
	}
}
