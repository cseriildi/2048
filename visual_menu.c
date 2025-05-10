#include "2048.h"

static void update_menu(t_win *menu)
{
	// mvwprintw(menu->win, ROW_TITLE + 1, COL_TEXT, MENU_INFO);
		// mvwprintw(menu->win,
		// 	ROW_TITLE + MENU_OPTIONS_X_OFFSET + i,
		// 	COL_TEXT + MENU_OPTIONS_Y_OFFSET,
		// 	"%s", options[i]);
	box(menu->win, 0, 0);
	wattron(menu->win, A_BOLD); 
	print_centered(menu, 1, MENU_TITLE);
	wattroff(menu->win, A_BOLD); 
	print_centered(menu, 1, MENU_INFO);

	const char *options[MAX_SIZE_OPTIONS] = {"4 x 4", "5 x 5"};
	
	for (unsigned int i = 0; i < MAX_SIZE_OPTIONS; i++) {
		if (i == menu->scroll_offset) {
			wattron(menu->win, A_REVERSE);
		}
		//TODO: get rid of hardcoded values
		print_centered(menu, 3 + i, options[i]);
		wattroff(menu->win, A_REVERSE);
	}
	wrefresh(menu->win);
}

void	init_menu(t_board *board)
{
	board->menu.size_x = MENU_WIDTH;
	board->menu.size_y = MENU_HEIGHT;
	board->menu.win = newwin(board->menu.size_y, board->menu.size_x,
			board->screen_y / 2 - board->menu.size_y / 2,	// position y
			board->screen_x / 2 - board->menu.size_x / 2);	// position x
}

static t_result	resize_menu(t_board *board)
{
	t_result res;
	delwin(board->menu.win);
	erase();
	refresh();
	cleanup_ncurses(board);
	// t_result res = init_ncurses(board);
	// if (res != SUCCESS)
	// 	return res;
	
	if ((res = window_resize_loop(board)) != SUCCESS)
	{
		return res;
	}
	init_menu(board);
	keypad(board->menu.win, TRUE);
	return SUCCESS;
}

t_result menu(t_board *board)
{
	t_result res;

	init_menu(board);
	// -- here
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
		else if (ch == KEY_RESIZE)
		{
			if ((res = resize_menu(board)) != SUCCESS)
			{
				return res;
			}
		}
		update_menu(&board->menu);
		ch = wgetch(board->menu.win);
	}
	board->size = (board->menu.scroll_offset == 0) ? 4 : 5;
	wclear(board->menu.win);
	wrefresh(board->menu.win);
	return SUCCESS;
}
