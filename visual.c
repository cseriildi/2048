#include "2048.h"

void update_menu(t_win *menu)
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

int menu(t_board *board)
{
	t_win menu = {0};
	//TODO: check the size, get rid of hardcoded values
	menu.size_x = 32;
	menu.size_y = 6;
	menu.win = newwin(menu.size_y, menu.size_x,
			board->screen_y / 2 - menu.size_y / 2, board->screen_x / 2 - menu.size_x / 2);

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
	return 0;
}

void update_board(t_board *board)
{
	t_tile tile;

	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			tile = board->tiles[i][j];
			wclear(tile.win.win);
			wbkgd(tile.win.win, COLOR_PAIR(tile.win.color));
			if (tile.number != 0)
				mvwprintw(tile.win.win, 1, 2, "%d", tile.number);
			wrefresh(tile.win.win);
		}
	}
}

void update_score(t_board *board)
{
	//TODO: read the score from a file
	//TODO: add the current player's score
	box(board->score_win.win, 0, 0);
	wrefresh(board->score_win.win);
}

int init_ncurses(t_board *board)
{
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
	if (menu(board) == 1)
		return 1; //TODO: define error codes

	//TODO: formula for resizing
	board->score_win.win = newwin(board->screen_y, board->screen_x - (board->size * 8) , 0, board->size * 8);
	if (board->score_win.win == NULL)
		return 1;
	
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			//TODO: formula for resizing
			board->tiles[i][j].win.win = newwin(3, 6, i * (3 + 1) + 1, j * (6 + 2) + 1);
			if (board->tiles[i][j].win.win == NULL)
				return 1;
			board->tiles[i][j].win.color = 1; //TODO: dynamic coloring based on value
		}
	}
	update_board(board);
	update_score(board);
	return 0;
}

void cleanup_ncurses(t_board *board)
{
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			if (board->tiles[i][j].win.win != NULL)
				delwin(board->tiles[i][j].win.win);
		}
	}

	if (board->score_win.win != NULL)
		delwin(board->score_win.win);
	if (stdscr != NULL)
		delwin(stdscr);
	endwin();
}

