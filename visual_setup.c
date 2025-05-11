#include "2048.h"

static void	define_colors(void)
{
	if (has_colors())
	{
		start_color();
		//TODO: select final colors
		short blue_shades[20] = {
			231, 189, 153, 117, 111, 110, 109, 81, 80, 79,
			74, 73, 72, 67, 66, 65, 60, 25, 24, 18
		};
		for (int i = 0; i < 20; ++i)
			init_pair(i + 1, COLOR_BLACK, blue_shades[i]);
	}
}

t_result	setup_menu_window(t_board *board)
{
	board->menu.scroll_offset = 0;
	board->menu.size_x = MENU_WIDTH;
	board->menu.size_y = MENU_HEIGHT;
	board->menu.win = newwin(board->menu.size_y, board->menu.size_x,
			board->screen_y / 2 - board->menu.size_y / 2,	// position y
			board->screen_x / 2 - board->menu.size_x / 2);	// position x
	if (board->menu.win == NULL)
		return NCURSES_FAILED;
	
	return SUCCESS;
}

t_result	setup_board_window(t_board *board)
{
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			t_tile *tile = &board->tiles[i][j];
			//TODO: formula for resizing
			tile->win.size_x = MIN_TILE_X;
			tile->win.size_y = MIN_TILE_Y;
			tile->win.pos_x = j * (MIN_TILE_X + MIN_TILE_SPACING * 2) + 1;
			tile->win.pos_y = i * (MIN_TILE_Y + MIN_TILE_SPACING) + 1;
			tile->win.win = newwin(
						tile->win.size_y,
						tile->win.size_x,
						tile->win.pos_y,
						tile->win.pos_x);
			if (tile->win.win == NULL)
				return NCURSES_FAILED;
		}
	}
	return SUCCESS;
}

t_result	setup_score_window(t_board *board)
{
	//TODO: formula for resizing
	int total_board_width = board->size * (MIN_TILE_X + MIN_TILE_SPACING * 2);
	board->score_win.size_x = board->screen_x - total_board_width;
	board->score_win.size_y = board->screen_y;
	board->score_win.pos_x = total_board_width;
	board->score_win.pos_y = 0;
	board->score_win.win = newwin(
								board->score_win.size_y,
								board->score_win.size_x,
								board->score_win.pos_y,
								board->score_win.pos_x);
	if (board->score_win.win == NULL)
		return NCURSES_FAILED;
	return SUCCESS;
}

t_result	setup_windows_error(t_board *board)
{
	t_result result;
	
	result = setup_menu_window(board);
	if (result == SUCCESS && !board->size)
		result = get_grid_size(board);
	if (result == SUCCESS)
		result = setup_board_window(board);
	if (result == SUCCESS)
		result = setup_score_window(board);
	return result;
}

void init_ncurses(void)
{
	initscr();
	noecho(); // user typed input will not be displayed on screen
	cbreak(); // disables line buffering; typed characters immediately available
	curs_set(0); // hide CLI cursor
	ESCDELAY = 25;
	mousemask(ALL_MOUSE_EVENTS, NULL);
}

t_result	setup_ncurses(t_board *board)
{
	t_result result = SUCCESS;

	init_ncurses();
	define_colors();
	// check if the screen is big enough for the game
	if ((result = window_size_check(board)) != SUCCESS)
		return result;
	// window creation
	if ((result = setup_windows_error(board)) != SUCCESS)
		return result;
	return SUCCESS;
}
