#include "2048.h"

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

t_result init_ncurses(t_board *board)
{
	t_result result = SUCCESS;

	initscr();
	noecho(); // user typed input will not be displayed on screen
	cbreak(); // disables line buffering; typed characters immediately available
	curs_set(0); // hide CLI cursor
	ESCDELAY = 25;

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

	getmaxyx(stdscr, board->screen_y, board->screen_x); //TODO: check if screen is big enough
	if ((result = menu(board)) != SUCCESS)
		return result;

	//TODO: formula for resizing
	board->score_win.size_x = board->screen_x - (board->size * 8);
	board->score_win.size_y = board->screen_y;
	board->score_win.pos_x = board->size * 8;
	board->score_win.pos_y = 0;
	board->score_win.win = newwin(board->score_win.size_y,  board->score_win.size_x, 
			board->score_win.pos_y, board->score_win.pos_x);
	if (board->score_win.win == NULL)
		return NCURSES_FAILED;
	
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			t_tile *tile = &board->tiles[i][j];
			//TODO: formula for resizing
			tile->win.size_x = 6;
			tile->win.size_y = 3;
			tile->win.pos_x = j * (6 + 2) + 1;
			tile->win.pos_y = i * (3 + 1) + 1;
			tile->win.win = newwin(tile->win.size_y, 
				tile->win.size_x, 
				tile->win.pos_y, 
				tile->win.pos_x);

			if (tile->win.win == NULL)
				return 1;
			tile->win.color = 1; //TODO: dynamic coloring based on value
		}
	}
	return SUCCESS;
}
