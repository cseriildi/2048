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

static void update_menu(t_win *menu)
{
	box(menu->win, 0, 0);
	wattron(menu->win, A_BOLD); 
	print_centered(menu, 1, "Let's play 2048!");
	wattroff(menu->win, A_BOLD); 
	print_centered(menu, 1, "Select grid size:");

	const char *options[2] = {"4 x 4", "5 x 5"};
	
	for (unsigned int i = 0; i < 2; i++) {
		if (i == menu->scroll_offset) {
			wattron(menu->win, A_REVERSE);
		}
		//TODO: get rid of hardcoded values
		print_centered(menu, 3 + i, options[i]);
		wattroff(menu->win, A_REVERSE);
	}
	wrefresh(menu->win);
}

static t_result menu(t_board *board)
{
	//TODO: check the size, get rid of hardcoded values
	board->menu.size_x = 32;
	board->menu.size_y = 6;
	board->menu.win = newwin(board->menu.size_y, board->menu.size_x,
		board->screen_y / 2 - board->menu.size_y / 2, board->screen_x / 2 - board->menu.size_x / 2);
		
	if (board->menu.win == NULL)
		return NCURSES_FAILED;
	
	board->menu.scroll_offset = 0;
	update_menu(&board->menu);
	keypad(board->menu.win, TRUE);

	int ch = wgetch(board->menu.win);
	while (ch != '\n')
	{
		if (ch == KEY_UP)
			board->menu.scroll_offset = 0;
		else if (ch == KEY_DOWN)
			board->menu.scroll_offset = 1;
		else if (ch == ESCAPE)
		{
			delwin(board->menu.win);
			return 1;
		}
		update_menu(&board->menu);
		ch = wgetch(board->menu.win);
	}
	board->size = (board->menu.scroll_offset == 0) ? 4 : 5;
	wclear(board->menu.win);
	wrefresh(board->menu.win);
	return SUCCESS;
}

t_result	setup_windows_error(t_board *board)
{
	// game window = individual tiles
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			t_tile *tile = &board->tiles[i][j];
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

t_result	resize_loop(t_board *board)
{
	keypad(stdscr, TRUE);
	mvprintw(ROW_TITLE,COL_TEXT,"terminal too small");
	mvprintw(ROW_TITLE + 1,COL_TEXT,"size (%i,%i) need (%i,%i)",
		board->screen_x, board->screen_y,
		board->min_screen_x, board->min_screen_y);
	refresh();
	int ch = getch();
	if (ch == ESCAPE)
		return (USER_EXIT); // this needs proper exit cleanup code
	else if (ch != KEY_RESIZE)
		return (SUCCESS);
	getmaxyx(stdscr, board->screen_y, board->screen_x);
	keypad(stdscr, FALSE);
	return (SUCCESS);
}

t_result board_size_check(t_board *board)
{
	while (board->screen_x < board->min_screen_x ||
		   board->screen_y < board->min_screen_y)
	{
		t_result result = resize_loop(board);
		if (result != SUCCESS)
			return result;
	}
	return SUCCESS;
}

t_result	window_resize_loop(t_board *board)
{
	t_result result = SUCCESS;

	getmaxyx(stdscr, board->screen_y, board->screen_x);
	unsigned int min_board_x = MAX_BOARD_SIZE * (MIN_TILE_X + MIN_TILE_SPACING * 2);
	board->min_screen_x = min_board_x + MIN_SCORE_X;
	board->min_screen_y = MAX_BOARD_SIZE * (MIN_TILE_Y + MIN_TILE_SPACING) + 1;
	if ((result = board_size_check(board)) != SUCCESS)
		return result;
	return SUCCESS;
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
	if ((result = window_resize_loop(board)) != SUCCESS)
		return result;
	// game mode selection
	if (!board->size && (result = menu(board)) != SUCCESS)
		return result;
	// window creation
	if ((result = setup_windows_error(board)) != SUCCESS)
		return result;
	return SUCCESS;
}
