#include "2048.h"

void update_menu(t_board *board)
{
	if (board->game_over)
	{
		box(board->menu.win, 0, 0);
		wbkgd(board->menu.win, COLOR_PAIR(COLOR_GAMEOVER));
		wattron(board->menu.win, A_BOLD);
		print_centered(&board->menu, 1, GAME_OVER1);
		print_centered(&board->menu, 3, GAME_OVER2);
		print_centered_number(&board->menu, 4, board->score);
		wattroff(board->menu.win, A_BOLD);
	}
	else
	{
		wbkgd(board->menu.win, COLOR_PAIR(COLOR_MENU));
		wattron(board->menu.win, A_BOLD); 
		print_centered(&board->menu, ROW_TITLE, MENU_TITLE);
		wattroff(board->menu.win, A_BOLD); 
		print_centered(&board->menu, ROW_TITLE + 1, MENU_INFO);

		const char *options[MAX_SIZE_OPTIONS] = {"4 x 4", "5 x 5"};
		
		for (unsigned int i = 0; i < MAX_SIZE_OPTIONS; i++) {
			if (i == board->menu.scroll_offset) {
				wattron(board->menu.win, A_REVERSE);
			}
			print_centered(&board->menu, ROW_TITLE + 3 + i, options[i]);
			wattroff(board->menu.win, A_REVERSE);
		}
	}
	wrefresh(board->menu.win);
}

static t_result	resize_menu(t_board *board)
{
	t_result res;
	delwin(board->menu.win);
	erase();
	refresh();
	cleanup_ncurses(board);

	if ((res = window_size_check(board)) != SUCCESS)
		return res;
	res = setup_menu_window(board);
	keypad(board->menu.win, TRUE);
	return res;
}

t_result get_grid_size(t_board *board)
{
	t_result res;

	update_menu(board);
	keypad(board->menu.win, TRUE);

	int ch = wgetch(board->menu.win);
	while (ch != '\n')
	{
		if (ch == KEY_UP)
			board->menu.scroll_offset = 0;
		else if (ch == KEY_DOWN)
			board->menu.scroll_offset = 1;
		else if (ch == ESCAPE)
			return USER_EXIT;
		else if (ch == KEY_RESIZE && (res = resize_menu(board)) != SUCCESS)
			return res;
		
		update_menu(board);
		ch = wgetch(board->menu.win);
	}
	wbkgd(board->menu.win, COLOR_PAIR(COLOR_DEFAULT));
	board->size = (board->menu.scroll_offset == 0) ? 4 : 5;
	wclear(board->menu.win);
	wrefresh(board->menu.win);
	return window_size_check(board);
}
