#include "2048.h"

static bool	merge_left_sim(t_board *board, int x, int y) {
	return (x + 1 < board->size && board->tiles[y][x + 1].number == board->tiles[y][x].number);
}

static bool	merge_right_sim(t_board *board, int x, int y) {
	return (x - 1 >= 0 && board->tiles[y][x - 1].number == board->tiles[y][x].number);
}

static bool	merge_up_sim(t_board *board, int x, int y) {
	return (y + 1 < board->size && board->tiles[y + 1][x].number == board->tiles[y][x].number);
}

static bool	merge_down_sim(t_board *board, int x, int y) {
	return (y - 1 >= 0 && board->tiles[y - 1][x].number == board->tiles[y][x].number);
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
				if (merge && board->tiles[y][x].number > 0 && merge(board, x, y))
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
				if (merge && board->tiles[y][x].number > 0 && merge(board, x, y))
					return (true);
			}
		}
	}
	return (false);
}

static bool	is_move_possible(t_board *board)
{
	return (simulate_merge_found(board, LEFT, merge_left_sim)
		|| simulate_merge_found(board, RIGHT, merge_right_sim)
		|| simulate_merge_found(board, UP, merge_up_sim)
		|| simulate_merge_found(board, DOWN, merge_down_sim));
}

void	check_game_over(t_board *board)
{
	if (!board->game_over && board->empty_tiles == 0 && !is_move_possible(board))
		board->game_over = true;
	if (board->game_over)
	update_menu(board);	
}
