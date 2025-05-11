#pragma once

# include "libft/libft.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#include <ncurses.h>

#define is_power_of_two(n) n > 0 && (n & (n - 1)) == 0

#define ESCAPE 27

#define MAX_BOARD_SIZE 5
#define MAX_SIZE_OPTIONS 2

#define SCORE_FILE "scores.txt"
#define SCORE_LIST_SIZE 100

#define ROW_TITLE 1	// box border has 0
#define COL_TEXT 1	// box border has 0
#define MENU_WIDTH 24
#define MENU_HEIGHT 7
#define MENU_TITLE "Let's play 2048!" // 16 chars
#define MENU_INFO "Select grid size:" // 17 chars
#define MENU_OPTIONS_X_OFFSET 3
#define MENU_OPTIONS_Y_OFFSET 1
#define SCORE_TITLE "Top Scores" // 11 chars
#define MIN_TILE_X 6
#define MIN_TILE_Y 3
#define MIN_TILE_SPACING 1
#define MIN_SCORE_X 16
#define SCORE_WIN_X 18
#define WINDOW_SPACING 1
#define GAME_OVER1 "Game Over!"
#define GAME_OVER2 "Your score is"
#define STATS1 "Your stats"
#define STATS2 "Your score:"
#define STATS3 "Max tile:"
#define STATS4 "Goal:"

#define SCORE_PRINT_START 0
#define MAX_TILE_PRINT_START -5

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
	unsigned int 	number;
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
	t_tile	tiles[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

	t_win	score_win;
	t_win	menu;
	unsigned int score;
	unsigned int max_tile_value;
	unsigned int screen_x;
	unsigned int screen_y;
	unsigned int min_screen_x;
	unsigned int min_screen_y;

	unsigned int top_scores[SCORE_LIST_SIZE];

	char *ascii_numbers[10][4];

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
	USER_EXIT,
}	t_result;

//init
t_result	setup_ncurses(t_board *board);
t_result	init_score(t_board *board);
void		init_board(t_board *board);

// ncusrses
void		update_board(t_board *board);
void		update_score(t_board *board);
t_result	resize_window(t_board *board, int ch);
t_result	get_grid_size(t_board *board);
t_result 	board_size_check(t_board *board);
t_result	window_resize_loop(t_board *board);
t_result	setup_windows_error(t_board *board);
// --- new
t_result	window_size_check(t_board *board);
// t_result	window_too_small_loop(t_board *board);
t_result	resize_gameloop(t_board *board, int ch);

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


t_result	write_score_to_file(t_board *board);

//utils
unsigned int	get_center_pos(t_win *win, unsigned int size);
void		print_centered(t_win *win, int row, const char *str);
void		print_centered_number(t_win *win, int row, unsigned int number);
void		print_stats(t_board *board, unsigned int row);

void		init_menu(t_board *board);
void		update_menu(t_board *board);
t_result	setup_menu_window(t_board *board);

// ascii art
int	ascii_fits(t_tile *tile, t_board *board);
void print_ascii_centered(int ascii_width, t_tile *tile, t_board *board);
void	init_ascii_numbers(t_board *board);