#include "2048.h"
#include <unistd.h>

int main(void)
{
	t_board board = {0};

	//TODO: check WIN_VALUE " This value is taken into account only if it is a power of 2"
	
	//TODO: print instructions
	
	//TODO: write best score to file

	//TODO: ascii art for numbers
	
	if (init_ncurses(&board) == 1)
	{
		cleanup_ncurses(&board);
		return 0;
	}
	
	init_board(&board);
	init_score(&board);
	game_loop(&board);
	cleanup_ncurses(&board);
	return 0;
}
