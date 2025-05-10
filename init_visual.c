#include "2048.h"

static void update_menu(t_win *menu)
{
	box(menu->win, 0, 0);
	//TODO: center the text
	mvwprintw(menu->win, 1, 1, "Let's play 2048!");
	mvwprintw(menu->win, 2, 1, "Select grid size:");
	const char *options[2] = {"4 x 4", "5 x 5"};
	
	for (unsigned int i = 0; i < 2; i++) {
		if (i == menu->scroll_offset) {
			wattron(menu->win, A_REVERSE);
		}
		//TODO: get rid of hardcoded values
		mvwprintw(menu->win, 3 + i, 2, "%s", options[i]);
		wattroff(menu->win, A_REVERSE);
	}
	wrefresh(menu->win);
}

static t_result menu(t_board *board)
{
	t_win menu = {0};
	//TODO: check the size, get rid of hardcoded values
	menu.size_x = 32;
	menu.size_y = 6;
	menu.win = newwin(menu.size_y, menu.size_x,
			board->screen_y / 2 - menu.size_y / 2, board->screen_x / 2 - menu.size_x / 2);

	if (menu.win == NULL)
		return NCURSES_FAILED;
	update_menu(&menu);
	keypad(menu.win, TRUE);
	int ch = wgetch(menu.win);
	while (ch != '\n')
	{
		if (ch == KEY_UP)
			menu.scroll_offset = 0;
		else if (ch == KEY_DOWN)
			menu.scroll_offset = 1;
		else if (ch == ESCAPE)
		{
			delwin(menu.win);
			return 1;
		}
		update_menu(&menu);
		ch = wgetch(menu.win);
	}
	board->size = (menu.scroll_offset == 0) ? 4 : 5;
	wclear(menu.win);
	wrefresh(menu.win);
	delwin(menu.win);
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
			//TODO: formula for resizing
			board->tiles[i][j].win.win = newwin(3, 6, i * (3 + 1) + 1, j * (6 + 2) + 1);
			if (board->tiles[i][j].win.win == NULL)
				return NCURSES_FAILED;
		}
	}
	return SUCCESS;
}
