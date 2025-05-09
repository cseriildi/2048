#include "2048.h"
#include <unistd.h>

int main(void)
{
	t_board board = {0};

	//init_board(&board);
/* 	while (board.game_over == false)
	{
		spawn_number(&board);
		if (board.empty_tiles == 0)
			board.game_over = true;
	}
	debug_print(&board); */

	//TODO: check WIN_VALUE " This value is taken into account only if it is a power of 2"


	//TODO: print instructions

	//TODO: spawn first 2 numbers
	//TODO: game logic
	
	//TODO: spawn random empty tile, 2 -> 90%, 4 -> 10%

	//TODO: write best score to file
	//TODO: ascii art for numbers


	board.size = 5;
	if (init_ncurses(&board) == 1)
	{
		cleanup_ncurses(&board);
		return 0;
	}

	game_loop(&board);
	cleanup_ncurses(&board);
	return 0;
}
