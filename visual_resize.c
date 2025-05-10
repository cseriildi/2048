#include "2048.h"

t_result	resize_window(t_board *board, int ch)
{
	t_result	res;

	if (ch != KEY_RESIZE)
		return SUCCESS;
	erase();
	refresh();
	cleanup_ncurses(board);
	// res = setup_ncurses(board);
	// printf("resizing window to %i x %i\n", board->screen_x, board->screen_y);
	if ((res = window_resize_loop(board)) != SUCCESS)
		return res;
	if ((res = setup_windows_error(board)) != SUCCESS)
		return res;
	keypad(board->score_win.win, TRUE);
	update_board(board);
	update_score(board);
	return SUCCESS;
}
