#include "2048.h"

int main(void)
{
	t_board board = {0};
	t_result result;

	//TODO: check WIN_VALUE " This value is taken into account only if it is a power of 2"
	if (false) //WIN_VALUE not power of 2
		return print_error(WIN_VALUE_ERROR);

	if ((result = init_score(&board)) != SUCCESS)
		return print_error(result);

	if ((result = setup_ncurses(&board)) == SUCCESS)
	{
		init_board(&board);
		game_loop(&board);
		result = write_score_to_file(&board);
	}
	cleanup_ncurses(&board);
	return print_error(result);
}
