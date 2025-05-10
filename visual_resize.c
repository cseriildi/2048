#include "2048.h"

t_result	resize_gameloop(t_board *board, int ch)
{
	t_result	res;

	if (ch != KEY_RESIZE)
		return SUCCESS;
	erase();
	refresh();
	cleanup_ncurses(board);
	// res = setup_ncurses(board);
	// printf("resizing window to %i x %i\n", board->screen_x, board->screen_y);
	if ((res = window_size_check(board)) != SUCCESS)
		return res;
	if ((res = setup_windows_error(board)) != SUCCESS)
		return res;
	keypad(board->score_win.win, TRUE);
	update_board(board);
	update_score(board);
	return SUCCESS;
}

// t_result 	board_size_check(t_board *board)
static t_result window_too_small_loop(t_board *board)
{
	while (board->screen_x < board->min_screen_x ||
		   board->screen_y < board->min_screen_y)
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
		// else if (ch != KEY_RESIZE)
		// 	return (SUCCESS);
		getmaxyx(stdscr, board->screen_y, board->screen_x);
		keypad(stdscr, FALSE);
	}
	return SUCCESS;
}

// t_result	window_resize_loop(t_board *board)
t_result	window_size_check(t_board *board)
{
	getmaxyx(stdscr, board->screen_y, board->screen_x);
	unsigned int min_board_x = MAX_BOARD_SIZE * (MIN_TILE_X + MIN_TILE_SPACING * 2);
	board->min_screen_x = min_board_x + MIN_SCORE_X;
	board->min_screen_y = MAX_BOARD_SIZE * (MIN_TILE_Y + MIN_TILE_SPACING) + 1;
	return window_too_small_loop(board);
}
