#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h> // TODO: remove
#include <time.h>
#include <unistd.h>

#include <ncurses.h>

#define ESCAPE 27

enum e_const
{
	WIN_VALUE = 2048
};

typedef struct s_win {
	WINDOW			*win;
	unsigned int	size_x;
	unsigned int	size_y;
	unsigned int	pos_x;
	unsigned int	pos_y;
	unsigned int	scroll_offset;
	int				color;
} t_win;
typedef struct tile
{
	int 	number;
	bool	merged;
	t_win	win;
}	t_tile;

typedef struct board
{
	bool 	game_over;
	short 	size;
	int  	empty_tiles;
	t_tile	tiles[5][5];

	t_win	score_win;
	unsigned int score;
	unsigned int screen_x;
	unsigned int screen_y;

}	t_board;

int init_ncurses(t_board *board);
void cleanup_ncurses(t_board *board);
void update_board(t_board *board);
void game_loop(t_board *board);

void	init_board(t_board *board);
void	spawn_number(t_board *board);
void	debug_print(t_board *board);