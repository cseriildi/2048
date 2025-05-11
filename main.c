#include "2048.h"

int main(void)
{
	t_board board = {0};
	t_result result;

	if (is_power_of_two(WIN_VALUE) == false)
		return print_error(WIN_VALUE_ERROR);

	if ((result = setup_ncurses(&board)) == SUCCESS
		&& (result = init_score(&board)) == SUCCESS)
	{
		init_board(&board);
		game_loop(&board);
		result = write_score_to_file(&board);
	}
	cleanup_ncurses(&board);
	return print_error(result);
}
