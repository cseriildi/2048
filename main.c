#include "2048.h"

int main(void)
{
	t_board board;

	init_board(&board);
	while (board.game_over == false)
	{
		printf("\n");
		spawn_number(&board);
		debug_print(&board);
		sleep(1);
		exec_move(&board, LEFT);
		debug_print(&board);
		sleep(1);
		if (board.empty_tiles == 0)
			board.game_over = true;
	}
	debug_print(&board);
	//TODO: check WIN_VALUE " This value is taken into account only if it is a power of 2"
	//TODO: setup ncurses
	//TODO: keyhook for ESC
	//TODO: prompt for grid size
		//buttons 4 x 4 or 5 x 5
	//TODO: draw grid
		//print instructions
		//draw windows (tiles)
	//TODO: spawn first 2 numbers
	//TODO: keyhook for arrow keys
		//game logic
	//game start
	//TODO: spawn random empty tile, 2 -> 90%, 4 -> 10%

	//TODO: write best score to file

	//TODO: color tiles
	//TODO: ascii art for numbers

	//TODO: scores shown on the side

	return 0;
}
