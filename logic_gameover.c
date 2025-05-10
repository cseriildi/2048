#include "2048.h"

static bool	is_move_possible(t_board *board);
static bool	simulate_merge_found(
				t_board *board,
				t_direction dir,
				bool (*merge)(t_board *, int, int));
static bool	merge_left_sim(t_board *board, int x, int y);
static bool	merge_right_sim(t_board *board, int x, int y);
static bool	merge_up_sim(t_board *board, int x, int y);
static bool	merge_down_sim(t_board *board, int x, int y);

void	check_game_over(t_board *board)
{
	if (board->empty_tiles == 0)
	{
		if (!is_move_possible(board))
		{
			board->game_over = true;
			//TODO show in new pop up window
			wclear(board->score_win.win);
			mvwprintw(board->score_win.win, 1, 1, "Game Over");
			wrefresh(board->score_win.win);
		}
	}
}

static bool	is_move_possible(t_board *board)
{
	if (simulate_merge_found(board, LEFT, merge_left_sim))
		return (true);
	if (simulate_merge_found(board, RIGHT, merge_right_sim))
		return (true);
	if (simulate_merge_found(board, UP, merge_up_sim))
		return (true);
	if (simulate_merge_found(board, DOWN, merge_down_sim))
		return (true);
	return (false);
}

static bool	simulate_merge_found(
				t_board *board,
				t_direction dir,
				bool (*merge)(t_board *, int, int))
{
	// loop for moving left and up
	if (dir == LEFT || dir == UP)
	{
		for (int x = 0; x < board->size; x++)
		{
			for (int y = 0; y < board->size; y++)
			{
				if (merge && board->tiles[y][x].number > 0)
					if (merge(board, x, y))
						return (true);
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
				if (merge && board->tiles[y][x].number > 0)
					if (merge(board, x, y))
						return (true);
			}
		}
	}
	return (false);
}

static bool	merge_left_sim(t_board *board, int x, int y)
{
	int i = x + 1;
	if (i < board->size)
	{
		if (board->tiles[y][i].number == board->tiles[y][x].number)
		{
			return (true);
		}
	}
	return (false);
}

static bool	merge_right_sim(t_board *board, int x, int y)
{
	int i = x - 1;
	if (i >= 0)
	{
		if (board->tiles[y][i].number == board->tiles[y][x].number)
		{
			return (true);
		}
	}
	return (false);
}

static bool	merge_up_sim(t_board *board, int x, int y)
{
	int i = y + 1;
	if (i < board->size)
	{
		if (board->tiles[i][x].number == board->tiles[y][x].number)
		{
			return (true);
		}
	}
	return (false);
}

static bool	merge_down_sim(t_board *board, int x, int y)
{
	int i = y - 1;
	if (i >= 0)
	{
		if (board->tiles[i][x].number == board->tiles[y][x].number)
		{
			return (true);
		}
	}
	return (false);
}
