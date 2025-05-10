#include "2048.h"

static void	define_colors(void)
{
	if (has_colors()) //TODO: flag to not try to color the tiles
	{
		start_color();
		//TODO: select colors for numbers
		init_pair(1, COLOR_WHITE, COLOR_BLUE);
		init_pair(2, COLOR_WHITE, COLOR_GREEN);
		init_pair(3, COLOR_WHITE, COLOR_YELLOW);
		init_pair(4, COLOR_WHITE, COLOR_CYAN);
		init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
		init_pair(6, COLOR_WHITE, COLOR_RED);
		init_pair(7, COLOR_BLACK, COLOR_WHITE);
	}
}

static t_result	setup_windows_error(t_board *board)
{
	// game window = individual tiles
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			//TODO: formula for resizing
			board->tiles[i][j].win.win = newwin(
						MIN_TILE_Y,
						MIN_TILE_X,
						i * (MIN_TILE_Y + MIN_TILE_SPACING) + 1,
						j * (MIN_TILE_X + MIN_TILE_SPACING * 2) + 1);
			if (board->tiles[i][j].win.win == NULL)
				return 1; // TODO: error handling
			board->tiles[i][j].win.color = 1; //TODO: dynamic coloring based on value
		}
	}
	// score board window
	//TODO: formula for resizing
	board->score_win.size_x = board->screen_x - (board->size * 8);
	board->score_win.size_y = board->screen_y;
	board->score_win.pos_x = board->size * 8;
	board->score_win.pos_y = 0;
	board->score_win.win = newwin(board->score_win.size_y,  board->score_win.size_x, 
			board->score_win.pos_y, board->score_win.pos_x);
	if (board->score_win.win == NULL)
		return NCURSES_FAILED;
	return SUCCESS;
}

t_result init_ncurses(t_board *board)
{
	t_result result = SUCCESS;

	initscr();
	noecho(); // user typed input will not be displayed on screen
	cbreak(); // disables line buffering; typed characters immediately available
	curs_set(0); // hide CLI cursor
	ESCDELAY = 25;

	define_colors();

	getmaxyx(stdscr, board->screen_y, board->screen_x); //TODO: check if screen is big enough
	if ((result = menu(board)) != SUCCESS)
		return result;
	if ((result = setup_windows_error(board)) != SUCCESS)
		return result;
	return SUCCESS;
}
