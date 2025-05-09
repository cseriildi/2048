#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h> // TODO: remove
#include <time.h>
#include <unistd.h> // TODO: remove?

enum e_const
{
	WIN_VALUE = 2048
};

typedef struct tile
{
	int 	number;
	bool	merged;
}	t_tile;

typedef struct board
{
	bool 	game_over;
	short 	size;
	int  	empty_tiles;
	t_tile	tiles[5][5];
}	t_board;

typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_direction;

void	init_board(t_board *board);
void	spawn_number(t_board *board);
void	debug_print(t_board *board);

// move and merge handler
void	exec_move(t_board *board, t_direction dir);
// move and merge directions
void	merge_left(t_board *board, int x, int y);
void	move_left(t_board *board, int x, int y);
