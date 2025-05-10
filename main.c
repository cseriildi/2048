#include "2048.h"
#include <unistd.h>

int main(void)
{
	t_board board = {0};
	t_result result = SUCCESS;

	//TODO: check WIN_VALUE " This value is taken into account only if it is a power of 2"
	if (false) //WIN_VALUE not power of 2
		return print_error(WIN_VALUE_ERROR);

	//TODO: print instructions
	
	//TODO: ascii art for numbers
	
	if ((result = init_score(&board)) != SUCCESS)
		return print_error(result);

	if ((result = setup_ncurses(&board)) != SUCCESS)
	{
		cleanup_ncurses(&board);
		return print_error(result);
	}
	
	init_board(&board);
	game_loop(&board);
	cleanup_ncurses(&board);
	result = write_score_to_file(&board);

	return result;
}
