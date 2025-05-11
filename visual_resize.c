#include "2048.h"

t_result	resize_gameloop(t_board *board, int ch)
{
	if (ch != KEY_RESIZE)
		return SUCCESS;
	erase();
	refresh();
	cleanup_ncurses(board);

	t_result	res = SUCCESS;
	if ((res = window_size_check(board)) == SUCCESS
		&& (res = setup_windows_error(board)) == SUCCESS)
	{	
		keypad(board->score_win.win, TRUE);
		update_board(board);
		update_score(board);
		check_game_over(board);
	}
	return res;
}

static t_result window_too_small_loop(t_board *board)
{
	while (board->screen_x < board->min_screen_x ||
		   board->screen_y < board->min_screen_y)
	{
		keypad(stdscr, TRUE);
		erase();
		refresh();
		wbkgd(stdscr, COLOR_PAIR(COLOR_TOOSMALL_WINDOW));
		wattron(stdscr, A_BOLD);
		unsigned int x = board->screen_x / 2 - 18 / 2;
		unsigned int y = board->screen_y / 2 - 1;
		mvprintw(y,x,"terminal too small"); // 18
		wattroff(stdscr, A_BOLD);
		unsigned int len = numlen(board->screen_x);
		len += numlen(board->screen_y);
		len += numlen(board->min_screen_x);
		len += numlen(board->min_screen_y);
		x = board->screen_x / 2 - (len + 17) / 2;
		y += 2;
		attron(COLOR_PAIR(COLOR_TOOSMALL_TEXT));
		mvprintw(y, x,"size (%i,%i) need (%i,%i)", // 17 + len
			board->screen_x, board->screen_y,
			board->min_screen_x, board->min_screen_y);
		attroff(COLOR_PAIR(COLOR_TOOSMALL_TEXT));
		if (getch() == ESCAPE)
			return (USER_EXIT);
		getmaxyx(stdscr, board->screen_y, board->screen_x);
		keypad(stdscr, FALSE);
	}
	return SUCCESS;
}

t_result	window_size_check(t_board *board)
{
	t_result res;
	getmaxyx(stdscr, board->screen_y, board->screen_x);

	unsigned int min_size = board->size ? board->size : MIN_BOARD_SIZE;

	unsigned int min_board_x = min_size * (MIN_TILE_X + MIN_TILE_SPACING * 2);
	board->min_screen_x = min_board_x + MIN_SCORE_X + WINDOW_SPACING * 3;
	board->min_screen_y = min_size * (MIN_TILE_Y + MIN_TILE_SPACING) + 1;
	res = window_too_small_loop(board);
	wbkgd(stdscr, COLOR_PAIR(0));
	if (res == SUCCESS)
	{
		erase();
		refresh();
	}
	return res;
}
