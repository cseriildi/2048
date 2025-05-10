#pragma once

# include "libft/libft.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#include <ncurses.h>

#define ESCAPE 27
#define MAX_SIZE 5

#define SCORE_FILE "scores.txt"
#define SCORE_LIST_SIZE 30  //TODO: check on the size of the array

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
	bool 	win;
	bool	spawn;
	short 	size;
	int  	empty_tiles;
	t_tile	tiles[MAX_SIZE][MAX_SIZE];

	t_win	score_win;
	unsigned int score;
	unsigned int screen_x;
	unsigned int screen_y;

	unsigned int top_scores[SCORE_LIST_SIZE];

}	t_board;

typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_direction;

typedef enum e_result
{
	SUCCESS,
	CANT_OPEN_FILE,
	NCURSES_FAILED,
	WIN_VALUE_ERROR,
	SCORE_LIST_SIZE_ERROR,
}	t_result;

//init
t_result	init_score(t_board *board);
void		init_board(t_board *board);

// ncusrses
t_result	init_ncurses(t_board *board);
void		update_board(t_board *board);
void		update_score(t_board *board);

// main game logic
void		game_loop(t_board *board);
void		check_game_over(t_board *board);
void		spawn_number(t_board *board);
void		exec_move(t_board *board, t_direction dir);

// logic helpers for move & merge
void		traverse_board(
	t_board *board,
	t_direction dir,
			void (*move)(t_board *, int, int),
			void (*merge)(t_board *, int, int));
void		reset_merged(t_board *board);

// move and merge directions
void		move_left(t_board *board, int x, int y);
void		move_right(t_board *board, int x, int y);
void		move_up(t_board *board, int x, int y);
void		move_down(t_board *board, int x, int y);
void		merge_left(t_board *board, int x, int y);
void		merge_right(t_board *board, int x, int y);
void		merge_up(t_board *board, int x, int y);
void		merge_down(t_board *board, int x, int y);

// cleanup
t_result	write_score_to_file(t_board *board);
t_result	print_error(t_result result);
void		cleanup_ncurses(t_board *board);

// debug functions
void		debug_print(t_board *board);
void		debug_move(t_board *board);