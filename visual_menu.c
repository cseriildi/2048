#include "2048.h"

static void update_menu(t_win *menu)
{
	box(menu->win, 0, 0);
	//TODO: center the text
	mvwprintw(menu->win, ROW_TITLE, COL_TEXT, MENU_TITLE);
	mvwprintw(menu->win, ROW_TITLE + 1, COL_TEXT, MENU_INFO);
	const char *options[MAX_SIZE_OPTIONS] = {"4 x 4", "5 x 5"};
	
	for (unsigned int i = 0; i < MAX_SIZE_OPTIONS; i++) {
		if (i == menu->scroll_offset) {
			wattron(menu->win, A_REVERSE);
		}
		mvwprintw(menu->win,
			ROW_TITLE + MENU_OPTIONS_X_OFFSET + i,
			COL_TEXT + MENU_OPTIONS_Y_OFFSET,
			"%s", options[i]);
		wattroff(menu->win, A_REVERSE);
	}
	wrefresh(menu->win);
}

t_result menu(t_board *board)
{
	t_win menu = {0};

	menu.size_x = MENU_WIDTH;
	menu.size_y = MENU_HEIGHT;
	menu.win = newwin(menu.size_y, menu.size_x,
			board->screen_y / 2 - menu.size_y / 2,	// position y
			board->screen_x / 2 - menu.size_x / 2);	// position x

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
