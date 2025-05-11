#include "2048.h"

int main(void)
{
	t_board board = {0};
	t_result result;

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
