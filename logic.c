#include "2048.h"

void	spawn_number(t_board *board)
{
	short tile;
	short number;
	
	tile =  rand() % (board->empty_tiles);
	number = rand() % 10;
	if (number < 9)
		number = 2;
	else
		number = 4;
	printf("tile: %d || number: %d\n", tile, number);
	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 5; b++)
		{
			if (board->tiles[a][b].number == 0)
			{
				if (tile == 0)
				{
					board->tiles[a][b].number = number;
					board->empty_tiles--;
					return ;
				}
				tile--;
			}
		}
	}
}



void game_loop(t_board *board)
{
	keypad(board->score_win.win, TRUE);
	int ch;
	while ((ch = wgetch(board->score_win.win)) != ESCAPE)
	{
		//TODO: add game logic
		/* 		if (ch == KEY_UP)
			
		else if (ch == KEY_DOWN)
			
		else if (ch == KEY_LEFT)
			
		else if (ch == KEY_RIGHT) */

		
		update_board(board);
	}
}